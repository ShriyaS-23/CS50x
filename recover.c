#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)//checking for 2 command line arguments
    {
        printf("Usage: ./recover filename");
        return 1;
    }

    FILE *memCard = fopen(argv[1], "r");//opening input file

    if (memCard == NULL)//checking if input file is empty
    {
        printf("Error");
        return 1;
    }

    int counter = 0;

    BYTE buffer[512];

    char image[8];

    FILE *jpg;

    int x = x = fread(buffer, sizeof(BYTE), 512, memCard);

    while (x == 512 || x == 1)
    {
        if (feof(memCard))
        {

        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)//checking for start of jpg
        {
            if (counter > 0)//first jpg
            {
                fclose(jpg);
                sprintf(image, "%03i.jpg", counter);
                jpg = fopen(image, "w");
                fwrite(buffer, sizeof(BYTE), 512, jpg);
                counter ++;
            }
            else
            {
                sprintf(image, "%03i.jpg", counter);
                jpg = fopen(image, "w");
                fwrite(buffer, sizeof(BYTE), 512, jpg);
                counter ++;
            }
        }
        else if (counter > 0)//middle of jpg
        {
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }

        x = fread(buffer, sizeof(BYTE), 512, memCard);
    }

    fclose(memCard);//closing input file
    fclose(jpg);//closing last output file
    return 0;

}
