#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    FILE *output = NULL;

    BYTE buffer[512];
    int JPEG_count = 0;

    char *filename = malloc(8 * sizeof(BYTE));


    while(fread(buffer, sizeof(BYTE)*512, 1, input)==1)
    {
        if((buffer[0] == 0xff && buffer[1] == 0xd8) && (buffer[2] == 0xff && (buffer[3] & 0xf0) == 0))
        {

            sprintf(filename, "%03i.jpg", JPEG_count);
            JPEG_count++;
            output  = fopen(filename, "w");
        }
        
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
        }
    }
    free(filename);
    fclose(output);
    fclose(input);
    return 0;
}
