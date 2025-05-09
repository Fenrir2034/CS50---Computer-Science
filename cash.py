# cash.py

from cs50 import get_float

def get_positive_float(prompt):
    """
    Prompt the user for a positive float value.

    Parameters:
    - prompt (str): The prompt to display to the user.

    Returns:
    - value (float): A positive float value.
    """
    while True:
        value = get_float(prompt)
        if value >= 0:
            return value
        else:
            print("Please enter a non-negative value.")

def main():
    # Prompt the user for the change owed
    dollars = get_positive_float("Change owed: $")

    # Convert dollars to cents
    cents = round(dollars * 100)

    # Initialize coin count
    coins = 0

    # Calculate the number of each coin needed
    coins += cents // 25  # quarters
    cents %= 25
    coins += cents // 10  # dimes
    cents %= 10
    coins += cents // 5   # nickels
    cents %= 5
    coins += cents        # pennies

    # Print the minimum number of coins
    print(coins)

if __name__ == "__main__":
    main()
