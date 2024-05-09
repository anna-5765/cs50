#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get Text Input From User
    string text = get_string("Text: ");

    // Calculate Number of Letters, Words, and Sentences in Text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate the Coleman-Liau Index
    double L = letters * 100.0 / words;   // average number of letters per 100 words in text
    double S = sentences * 100.0 / words; // average number of sentences per 100 words in text
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int index_r = round(index);

    // Identify and Print Reading Level
    if (index_r < 1)
        printf("Before Grade 1\n");
    else if (index_r >= 1 && index_r < 16)
        printf("Grade %i\n", index_r);
    else
        printf("Grade 16+\n");
}

// Count number of letters in input string
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isalpha(text[i]) > 0) // identifies alphabetical characters
        {
            letters += 1;
        }
        else
            continue;
    }
    return letters;
}

// Count number of words in input string
int count_words(string text)
{
    int words = 1; // no space after last word in text
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isblank(text[i]) > 0) // identifies spaces
        {
            words += 1;
        }
        else
            continue;
    }
    return words;
}

// Count number of sentences in input string
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // identifies ending punctuation
            sentences += 1;
        else
            continue;
    }
    return sentences;
}
