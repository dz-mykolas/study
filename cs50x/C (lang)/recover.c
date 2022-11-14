#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too many arguments.\n");
        return 1;
    }

    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    typedef uint8_t BYTE;

    bool ifFirst = true;

    // Filename array
    char filenameS[50];

    // Used for JPEG writing
    FILE *filename;

    // File counter
    int i = 0;

    // Block data
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (ifFirst == true)
            {
                ifFirst = false;
            }
            else
            {
                fclose(filename);
                i++;
            }
            sprintf(filenameS, "%03i.jpg", i);
            filename = fopen(filenameS, "w");
            fwrite(buffer, 1, BLOCK_SIZE, filename);
        }
        else
        {
            if (ifFirst == false)
            {
                fwrite(buffer, 1, BLOCK_SIZE, filename);
            }
        }
    }

    /* Close remaining files */
    // Loop file
    fclose(filename);
    // Data file
    fclose(inptr);

    return 0;
}