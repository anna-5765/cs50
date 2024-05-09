#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create global variables for ASCII uppercase/lowercase integer mapping
int cap[26];
int low[26];

string code_message(string plaintext, int key);

int main(int argc, string argv[])
{
    // Check number of command-line arguments
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if key value is a non-negative digit
    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert command line argument from string to int
    int key = atoi(argv[1]);

    // Get plaintext from user
    string plaintext = get_string("plaintext:  ");

    // Code cipher
    string ciphertext = code_message(plaintext, key);

    // Print ciphertext
    printf("ciphertext: ");
    for (int i = 0, l = strlen(ciphertext); i < l; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}

string code_message(string plaintext, int key)
{
    // Create ascii mapping for uppercase/lowercase letters
    for (int i = 0; i < 26; i++)
    {
        cap[i] = 65 + i;
        low[i] = 97 + i;
    }

    // Convert plaintext to ciphertext using key
    string ciphertext = plaintext; // initialize ciphertext the same size as plaintext
    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        // We are working with a capital letter
        if ((int) plaintext[i] >= 65 && (int) plaintext[i] <= 90)
        {
            int i_new = (((int) plaintext[i] - 65) + key) % 26; // calculate new index of letter using int representation
            ciphertext[i] = cap[i_new];
        }

        // We are working with a lowercase letter
        else if ((int) plaintext[i] >= 97 && (int) plaintext[i] <= 122)
        {
            int i_new = (((int) plaintext[i] - 97) + key) % 26; // calculate new index of letter using int representation
            ciphertext[i] = low[i_new];
        }
        else
            ciphertext[i] = plaintext[i];
    }

    return ciphertext;
}
