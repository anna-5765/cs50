// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 18278; // First three letters (26^3)+(26^2)+26
// const unsigned int N = 702; // First two letters (26^2)+26
// const unsigned int N = 26; // First letter Hash Function

// Hash table
node *table[N];

int word_count = 0;
bool loaded;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word
    int index = hash(word);

    // Create pointer to search hash table
    node *ptr = table[index];

    // Loop through dictionary and compare strings
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // First three letters hash function
    // Words sent to this function may include a-z or apostrophes, apostrophes are handled by
    // calculating as if it were an 'A'
    if (strlen(word) > 2)
    {
        if (!isalpha(word[0])) // look for apostrophes
            return ((26 * (0)) + (26 * 26 * (toupper(word[1]) - 'A')) + 676 + 26 + (toupper(word[2]) - 'A'));
        else if (!isalpha(word[1]))
            return ((26 * (toupper(word[0]) - 'A')) + (26 * 26 * (0)) + 676 + 26 + (toupper(word[2]) - 'A'));
        else if (!isalpha(word[2]))
            return ((26 * (toupper(word[0]) - 'A')) + (26 * 26 * (toupper(word[1]) - 'A')) + 676 + 26 + (0));
        else
            return ((26 * (toupper(word[0]) - 'A')) + (26 * 26 * (toupper(word[1]) - 'A')) + 676 + 26 + (toupper(word[2]) - 'A'));
    }
    else if (strlen(word) == 2)
    {
        if (!isalpha(word[0])) // look for apostrophes
            return (26 * (0) + 26 + (toupper(word[1]) - 'A'));
        else if (!isalpha(word[1]))
            return (26 * (toupper(word[0]) - 'A') + 26 + (0));
        else
            return (26 * (toupper(word[0]) - 'A') + 26 + (toupper(word[1]) - 'A'));
    }
    else
        return toupper(word[0]) - 'A';

    // // First two letters hash function
    // if (strlen(word) > 2)
    // {
    //     if (!isalpha(word[0])) // look for apostrophes
    //         return (26 * (0) + 26 + (toupper(word[1]) - 'A'));
    //     else if (!isalpha(word[1]))
    //         return (26 * (toupper(word[0]) - 'A') + 26 + (0));
    //     else
    //         return (26 * (toupper(word[0]) - 'A') + 26 + (toupper(word[1]) - 'A'));
    // }
    // else
    //     return toupper(word[0]) - 'A';

    // // First letter hash function
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create space for new hash table node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return 1;
        }

        // Copy the word into the new node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word
        int index = hash(word);

        // Insert node into hash table
        n->next = table[index];
        table[index] = n;

        // Index word count
        word_count += 1;
    }

    // Close the dictionary file
    fclose(dict);

    // Check variable
    loaded = true;

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
        return word_count;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Create traversal pointer and free memory
    node *ptr = NULL;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
