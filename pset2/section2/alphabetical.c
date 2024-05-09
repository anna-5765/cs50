#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string phrase = get_string("Enter a Phrase: ");

    for (int i = 0, length = strlen(phrase); i < length - 1; i++)
    {
        //Check if characters are NOT alphabetical
        if (phrase[i] > phrase[i+1])
        {
            printf("Not in alphabetical order.\n");
            return 0;
        }
    }
    printf("Alphabetical order!\n");
    return 0;

    // Print numbers for each character
    // for (int i = 0, length = strlen(phrase); i < length - 1; i++)
    // {
    //     printf("%i", phrase[i]);
    // }
    // printf("\n");
}
