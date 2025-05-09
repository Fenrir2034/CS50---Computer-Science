import os
import sqlite3

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd
from flask import url_for

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
conn = sqlite3.connect("finance.db", check_same_thread=False)
db = conn.cursor()

# Create tables if they don't exist
db.execute("""
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        hash TEXT NOT NULL,
        cash NUMERIC DEFAULT 10000.00
    )
""")

db.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        price NUMERIC NOT NULL,
        transacted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY(user_id) REFERENCES users(id)
    )
""")

db.execute("""
    CREATE TABLE IF NOT EXISTS stocks (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        FOREIGN KEY(user_id) REFERENCES users(id),
        UNIQUE(user_id, symbol)
    )
""")
conn.commit()

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    user_stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", (user_id,))
    cash = db.execute("SELECT cash FROM users WHERE id = ?", (user_id,)).fetchone()[0]
    return render_template("index.html", stocks=user_stocks, cash=cash)

from flask import redirect, render_template, request, session, url_for

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Ensure shares is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError("Shares must be a positive integer")
        except ValueError:
            return apology("Shares must be a positive integer")

        stock = lookup(symbol)
        if not stock:
            return apology("Invalid stock symbol")

        total_cost = stock["price"] * shares

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", (user_id,)).fetchone()[0]

        if cash < total_cost:
            return apology("Insufficient funds")

        # Perform the purchase transaction here
        # Update the user's cash balance and stock portfolio

        # Render a purchase confirmation template
        return render_template("purchase_confirmation.html", total_cost=usd(total_cost))

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("""
        SELECT symbol, shares, price, transacted_at FROM transactions WHERE user_id = ?
    """, (user_id,)).fetchall()
    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        user = db.execute("SELECT * FROM users WHERE username = ?", (username,)).fetchone()

        if not user or not check_password_hash(user[2], password):
            return apology("Invalid username and/or password")

        session["user_id"] = user[0]
        return redirect("/")
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Username is required")
        elif not password:
            return apology("Password is required")
        elif password != confirmation:
            return apology("Passwords must match")

        existing_user = db.execute("SELECT * FROM users WHERE username = ?", (username,)).fetchone()
        if existing_user:
            return apology("Username already exists")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", (username, generate_password_hash(password)))
        conn.commit()

        return redirect("/login")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))

        stock = lookup(symbol)
        if not stock:
            return apology("Invalid stock symbol")

        user_id = session["user_id"]
        user_stock = db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", (user_id, symbol)).fetchone()

        if not user_stock or user_stock["shares"] < shares:
            return apology("Insufficient shares")

        total_cash = stock["price"] * shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", (total_cash, user_id))
        db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? AND symbol = ?", (shares, user_id, symbol))

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   (user_id, symbol, -shares, stock["price"]))
        conn.commit()

        return redirect("/")
    else:
        user_id = session["user_id"]
        user_stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", (user_id,)).fetchall()
        return render_template("sell.html", user_stocks=user_stocks)

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")

        quote_data = lookup(symbol)
        if not quote_data:
            return apology("invalid symbol")

        return render_template("quote.html", quote_data=quote_data)
    else:
        return render_template("quote.html")

if __name__ == "__main__":
    app.run(debug=True)

