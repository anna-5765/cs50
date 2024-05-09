#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("What is your age? ");
    string phone_num = get_string("What is your phone number? ");
    printf("Name: %s\nAge: %i\nPhone Number: %s\n", name, age, phone_num);
}
