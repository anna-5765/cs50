#include <cs50.h>
#include <stdio.h>

void calc_coins(int change);

int main(void)
{
    int change;
    do
    {
       change = get_int("Change owed: "); //prompt user for change amount owed
    }
    while (change < 0); //prompt again if number not positive

    calc_coins(change);
}

void calc_coins(int change)
{
    int coins = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    while (change > 0)
    {
        if (change/quarter > 0)
        {
            change -= quarter;
            coins += 1;
        }
        else if (change/dime > 0)
        {
            change -= dime;
            coins += 1;
        }
        else if (change/nickel > 0)
        {
            change -= nickel;
            coins += 1;
        }
        else
        {
            change -= penny;
            coins += 1;
        }
    }
    printf("%i\n", coins);
}
