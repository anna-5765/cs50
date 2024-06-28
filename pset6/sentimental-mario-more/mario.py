# Build the Pyramid with a Gap in Mario Using a Chosen Height and "#"'s
from cs50 import get_int


def main():

    # Prompt user for pyramid height
    while True:
        height = int(get_int("Height: "))
        if height > 0 and height < 9:  # Limit input to 1-8
            break

    # Print elements by row
    for i in range(height):
        print_space(height - i - 1)        # Print leading spaces
        print_blocks(i + 1)                # Print right-aligned blocks
        print_space(2)                     # 2 space Gap
        print_blocks(i + 1)                # Print left-aligned blocks
        print()                            # Next line


def print_space(n):
    print(" " * n, end="")


def print_blocks(n):
    print("#" * n, end="")


main()
