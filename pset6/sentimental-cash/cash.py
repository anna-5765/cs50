# Ask how much change is owned, print number of coins
# Input change in dollars, eg. 0.50
from cs50 import get_float


def main():

    # Prompt user for change owed
    while True:
        change = get_float("Change: ")
        if change > 0:
            break

    # Calculate change in least number of coins
    calc_coins(change)


def calc_coins(change):

    # Avoid floating point imprecision, convert change to cents/ints
    cents = change * 100

    # Define coin values in cents
    quarter = 25
    dime = 10
    nickel = 5
    penny = 1

    coins = 0

    # Calculate change
    while cents > 0:
        if cents >= quarter:
            cents -= quarter
            coins += 1
        elif cents >= dime:
            cents -= dime
            coins += 1
        elif cents >= nickel:
            cents -= nickel
            coins += 1
        else:
            cents -= penny
            coins += 1

    print(coins)


main()
