#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Check if the memory card file opened successfully
    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    unsigned char buffer[512];

    // Initialize variables for tracking JPEGs and output files
    int jpeg_count = 0;
    FILE *jpeg = NULL;

    // Repeat until the end of the card is reached
    while (fread(buffer, 512, 1, card) == 1)
    {
        // Check if the current block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG file is already open, close it
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg = fopen(filename, "w");
            jpeg_count++;
        }

        // Write the current block to the JPEG file if it's open
        if (jpeg != NULL)
        {
            fwrite(buffer, 512, 1, jpeg);
        }
    }

    // Close any remaining files
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}
