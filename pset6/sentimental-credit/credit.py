# Report if credit card number is valid, if yes identify company
from cs50 import get_int
from math import trunc
import sys


def main():

    # Prompt user for credit card number
    credit = get_int("Number: ")
    credit_list = [int(i) for a, i in enumerate(str(credit))]  # convert number to iterable list

    # Validate card number
    validation(credit_list)

    # Identify company
    id_credit(credit_list)


# Calculate Luhn's Algorithm to validate card number  # test: 4003600000000014
def validation(credit):

    checksum = 0

    # Multiply every other digit by 2 starting from the second to last, add those digits together
    for i in credit[-2::-2]:
        prod_digit = i * 2
        if prod_digit > 9:
            checksum += trunc(prod_digit % 100 / 10) + prod_digit % 10  # sum double digits
        else:
            checksum += prod_digit

    # Add checksum to sum of remaining digits in credit
    for i in credit[-1::-2]:
        checksum += i

    # Card is valid if the checksum is divisible by 10
    if checksum % 10 != 0:
        print("INVALID")
        sys.exit(1)


# Identify company
def id_credit(credit):

    length = len(credit)
    first_num = credit[0]
    second_num = credit[1]

    if length == 13 and first_num == 4:
        print("VISA")
    elif length == 15 and first_num == 3 and (second_num == 4 or second_num == 7):
        print("AMEX")
    elif length == 16 and first_num == 4:
        print("VISA")
    elif length == 16 and first_num == 5 and (second_num >= 1 and second_num <= 5):
        print("MASTERCARD")
    else:
        print("INVALID")
        sys.exit(2)


main()
