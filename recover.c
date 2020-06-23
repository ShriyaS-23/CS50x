#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename");
        return 1;
    }

    FILE *memCard = fopen(argv[1], "r");

    if (memCard == NULL)
    {
        printf("Error");
        return 1;
    }

    int x = 512;

    int counter = 0;

    BYTE buffer[512];

    char image[8];

    FILE *jpg;

    while(x == 512 || x == 1)
    {
        x = fread(buffer, sizeof(BYTE), 512, memCard);
        
        if(feof(memCard))
        {
            
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
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
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }
    }

    fclose(memCard);
    fclose(jpg);
    return 0;

}
