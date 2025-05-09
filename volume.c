#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEADER_SIZE 44

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        printf("Could not open %s for writing.\n", argv[2]);
        fclose(input);
        return 1;
    }

    // Determine scaling factor
    float factor = atof(argv[3]);

    // Copy WAV header from input to output
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input, scale volume, and write updated data to output
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input)) {
        // Update volume of sample
        buffer *= factor;

        // Write updated sample to new file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
