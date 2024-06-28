# Make right-aligned pyramid in mario
from cs50 import get_int


def main():

    # Prompt user for pyramid height
    while True:
        height = int(get_int("Height: "))
        if height > 0 and height < 9:     # Limit input to 1-8
            break

    # Loop through rows and print elements
    for i in range(height):
        print_space(height, i)            # Print spaces using helper function
        print("#" * (i + 1))              # Print block


def print_space(height, row):
    # Print the number of spaces equal to the height - row (0 indexed so -1)
    print(" " * (height - row - 1), end="")


main()
