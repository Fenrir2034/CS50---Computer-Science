# readability.py

from cs50 import get_string

def calculate_grade(letters, words, sentences):
    """
    Calculate the Coleman-Liau grade level.

    Parameters:
    - letters (int): Number of letters in the text.
    - words (int): Number of words in the text.
    - sentences (int): Number of sentences in the text.

    Returns:
    - grade (int): Coleman-Liau grade level.
    """
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)

def get_text():
    """
    Prompt the user for text input.

    Returns:
    - text (str): The user-entered text.
    """
    return get_string("Text: ")

def main():
    text = get_text()

    # Count letters, words, and sentences
    letters = sum(c.isalpha() for c in text)
    words = text.count(' ') + 1
    sentences = text.count('.') + text.count('!') + text.count('?')

    # Calculate the Coleman-Liau grade level
    grade = calculate_grade(letters, words, sentences)

    # Output the result
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()
