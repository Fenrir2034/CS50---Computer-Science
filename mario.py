# mario.py

def get_height():
    """
    Prompt the user for the half-pyramid's height.

    Returns:
    - height (int): A positive integer between 1 and 8, inclusive.
    """
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
            else:
                print("Please enter a positive integer between 1 and 8.")
        except ValueError:
            print("Invalid input. Please enter a positive integer.")

def draw_pyramid(height):
    """
    Draw a double half-pyramid with a gap of two spaces between them.

    Parameters:
    - height (int): The height of each half-pyramid.
    """
    for i in range(1, height + 1):
        spaces_left = " " * (height - i)
        blocks_left = "#" * i
        spaces_gap = " " * 2
        blocks_right = "#" * i

        print(spaces_left + blocks_left + spaces_gap + blocks_right)

def main():
    height = get_height()
    draw_pyramid(height)

if __name__ == "__main__":
    main()
