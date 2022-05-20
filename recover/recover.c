#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // return 1 for incorrect argument
    if (argc != 2) {
        printf("USAGE: ./recover IMAGE\n");
    }

    // get file
    FILE *file = fopen(argv[1], "r");

    // return 1 for invalid file
    if (file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    // counter and buffer for input data
    int image_counter = 0;
    uint8_t buffer[512];

    // file and name for output data
    FILE *output = NULL;
    char *name = malloc(8*sizeof(char));

    while (fread(buffer, 1, 512, file) == 512) {
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255) {
            if (buffer[3] >= 224 && buffer[3] <= 236) {
                // create output file
                sprintf(name, "%03i.jpg", image_counter);
                output = fopen(name, "w");

                // increment counter
                image_counter++;
            }
        }
        // write buffer data to ouput
        if (output != NULL) {
            fwrite(buffer, 1, 512, output);
        }
    }

    // prevent memory leaks
    fclose(file);
    free(name);
    fclose(output);
}