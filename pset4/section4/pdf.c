#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

// Check if a file is pdf, first four bytes 37, 80, 68, 70
int main(int argc, string argv[])
{
    // Check first four bytes in given file
    string filename = argv[1];
    FILE *f = fopen(filename, "r");
    uint8_t buffer[4]; // creates space in memory to store some file info, unsigned(only positive) int that is 8 bits long (from stdint)
    fread(buffer, 1, 4, f);

    for (int i =0; i < 4; i++)
    {
        printf("%i\n", buffer[i]);
    }
    fclose(f);
}
