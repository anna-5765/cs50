#include <cs50.h>
#include <stdio.h>

int calc(long credit);
void id_credit(long credit);
int valid(int validation_num);

int main(void)
{
    long credit = get_long("Number: "); //prompt user for credit card number

    int validation_num = calc(credit);
    int validation = valid(validation_num);
    if (validation == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        //void id_credit(long credit);
        int count = 0;
        long count_credit = credit;
        int visa_13 = credit/(1e12);
        int amex = credit/(1e13);
        int visa_16 = credit/(1e15);
        int mastercard = credit/(1e14);

        // Get digit count
        while (count_credit > 0)
        {
            count_credit /= 10;
            count++;
        }

        // Check company
        if (count == 13 && visa_13 == 4)
            printf("VISA\n");
        else if (count == 15 && (amex == 34 || amex == 37))
            printf("AMEX\n");
        else if (count == 16 && visa_16 == 4)
            printf("VISA\n");
        else if (count == 16 && (mastercard >= 51 && mastercard <= 55))
            printf("MASTERCARD\n");
        else
            printf("INVALID\n");
    }
}

// Calculate Luhn's Algorithm
int calc(long credit)      // 4003600000000014
{
    int prod_sum = 0;
    long new_credit = credit;
    while (new_credit > 0)
    {
        int digit = new_credit % 100 / 10; //get second to last digit
        int prod_digit = digit * 2;
        if (prod_digit > 9)
        {
            prod_digit = prod_digit % 100 / 10 + prod_digit % 10; //sum double digits
        }
        prod_sum += prod_digit;
        new_credit /= 100; //remove last two digits
    }
    
    int left_sum = 0;
    long new_credit2 = credit;
    while (new_credit2 > 0)
    {
        int left_digit = new_credit2 % 10; //get last number
        left_sum += left_digit;
        new_credit2 /= 100; //remove last two digits
    }

    int validation_num = prod_sum + left_sum;
    //printf("%i\n", validation_num);

    return validation_num;
}

// Determine if card number satisfies Luhn's Algorithm
int valid(int validation_num)
{
    int validation;
    if (validation_num % 10 == 0)
    {
        validation = 1; //VALID
    }
    else
    {
        validation = 0; //INVALID
    }
    return validation;
}

// If card number valid, identify company
void id_credit(long credit)
{
    int count = 0;
    long count_credit = credit;
    int visa_13 = credit/(1e12);
    int amex = credit/(1e13);
    int visa_16 = credit/(1e15);
    int mastercard = credit/(1e14);

    // Get digit count
    while (count_credit > 0)
    {
        count_credit /= 10;
        count++;
    }

    // Check company
    if (count == 13 && visa_13 == 4)
        printf("VISA\n");
    else if (count == 15 && (amex == 34 || amex == 37))
        printf("AMEX\n");
    else if (count == 16 && visa_16 == 4)
        printf("VISA\n");
    else if (count == 16 && (mastercard >= 51 && mastercard <= 55))
        printf("MASTERCARD\n");
    else
        printf("INVALID\n");
}
