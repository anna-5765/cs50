#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calc_points(string ans);
string uppercase(string word);

// Create scrabble letters as points and global variables
int points_array[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt Player 1 & Player 2 for input
    string string1 = get_string("Player 1: ");
    string string2 = get_string("Player 2: ");

    // Calculate Points
    int ans1 = calc_points(uppercase(string1));
    int ans2 = calc_points(uppercase(string2));

    // Determine Winner
    if (ans1 > ans2)
        printf("Player 1 wins!\n");
    else if (ans2 > ans1)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
}

// Change input to uppercase
string uppercase(string word)
{
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        word[i] = toupper(word[i]);
    }
    return word;
}

// Calculate total points
int calc_points(string ans)
{
    int total = 0;
    for (int i = 0, n = strlen(ans); i < n; i++)
    {
        // manage cases outside of the alphabet like punctuation & symbols
        int point_index =
            (int) ans[i] - 65; // call index of point array based on letter integer - 'A'
        if (point_index > 25 || point_index < 0)
        {
            int points = 0;
            total += points;
        }

        // for letters, find point value and add to total
        else
        {
            int points = points_array[(int) ans[i] - 65];
            total += points;
        }
    }
    return total;
}
