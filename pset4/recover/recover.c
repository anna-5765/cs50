#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Error Check - more than one input argument
    if (argc != 2)
    {
        printf("Usage: ./recover [name of memory card]\n");
        return 1;
    }

    // Open Memory Card
    FILE *card = fopen(argv[1], "r");

    // Error Check - cannot open file
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    int block_size = 512; // FAT file system definition
    uint8_t buffer[block_size];

    // Iterate Over Memory Card
    int counter = 0;
    char *s = "###.jpg"; // save format
    char *filename = malloc(strlen(s) + 1); // create enough memory for filename string
    FILE *img = NULL;

    while (fread(buffer, 1, block_size, card) == block_size)
    {
        // Check for jpeg file header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // bitwise arithmetic comparing first four bits to 1110
        {
            if (counter == 0)
            {
                // Write jpeg to new file
                sprintf(filename, "%03i.jpg", counter); // print an integer with 3 digits to represent it
                img = fopen(filename, "w");
                fwrite(buffer, 1, block_size, img);

                counter += 1; // keep track of images
            }
            else
            {
                fclose(img); // close previous file

                // Write jpeg to new file
                sprintf(filename, "%03i.jpg", counter); // print an integer with 3 digits to represent it
                img = fopen(filename, "w");
                fwrite(buffer, 1, block_size, img);

                counter += 1; // keep track of images
            }
        }
        else
        {
            // Continue writing to jpeg
            if (img != NULL)
            {
                fwrite(buffer, 1, block_size, img);
            }
        }
    }
    // Close Files
    fclose(card);
    fclose(img);

    // Free Memory
    free(filename);
}
