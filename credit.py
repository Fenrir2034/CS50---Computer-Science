# credit.py

from cs50 import get_string

def get_card_number():
    """
    Prompt the user for a credit card number.

    Returns:
    - card_number (str): A string representing the credit card number.
    """
    while True:
        card_number = get_string("Credit card number: ")
        if card_number.isdigit():
            return card_number
        else:
            print("Please enter a numeric value.")

def validate_card(card_number):
    """
    Validate the credit card number and determine the card type.

    Parameters:
    - card_number (str): A string representing the credit card number.

    Returns:
    - card_type (str): A string representing the card type (AMEX, MASTERCARD, VISA, INVALID).
    """
    if len(card_number) == 15 and (card_number.startswith("34") or card_number.startswith("37")):
        return "AMEX"
    elif len(card_number) == 16 and card_number.startswith(("51", "52", "53", "54", "55")):
        return "MASTERCARD"
    elif (len(card_number) == 13 or len(card_number) == 16) and card_number.startswith("4"):
        return "VISA"
    else:
        return "INVALID"

def main():
    card_number = get_card_number()
    card_type = validate_card(card_number)
    print(card_type)

if __name__ == "__main__":
    main()

