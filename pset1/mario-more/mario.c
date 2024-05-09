#include <cs50.h>
#include <stdio.h>

void print_row(int length);
void print_space(int blank);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");   //prompt user for height of pyramids
    }
    while (height < 1 || height > 8);   //prompt again if height not within 1-8 inclusive

    //Build Adjacent Mario pyramids
    for (int i = 0; i < height; i++)
    {
        print_space(height - (i + 1));
        print_row(i + 1);               //right-aligned pyramid
        print_space(2);                 //double space
        print_row(i + 1);               //left-aligned pyramid
        printf("\n");                   //next line
    }
}

void print_space(int blank)             //fxn to print spaces per row
{
    for (int i = 0; i < blank; i++)
    {
        printf(" ");
    }
}

void print_row(int length)              //fxn to print #s per row
{
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
}


