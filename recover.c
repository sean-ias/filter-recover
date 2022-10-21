#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE; 
 
int main(int argc, char *argv[])
{
    //checking if there are only 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    //checking if the file is opened correctly
    if (file == NULL)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //j is num of images
    int j = 0;
    //array of 512 bytes
    BYTE bytes[512];
    //per img file name of 8 bytes
    char jpg[8];
    //img file
    FILE *img = NULL;
    //until the end of the file = reading 512 bytes to bytes array each step
    while (fread(bytes, sizeof(BYTE), 512, file))
    {
        //checking if it is jpeg header
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //if it isnt our 1st header, then close it
            if (j != 0)
            {
                fclose(img);
            }
            //open new header file and write it
            sprintf(jpg, "%03i.jpg", j++);
            img = fopen(jpg, "w");
        }
        //if it isnt our first header file write in it
        if (j != 0)
        {
            fwrite(bytes, sizeof(BYTE), 512, img);
        }
    }
    //closing the files
    fclose(file);
    fclose(img);
}