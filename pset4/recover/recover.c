#include<stdint.h>
#include <stdio.h>
#include <stdlib.h>

//creates a datatype called byte which uses a datatype called unit8_t to represent 8 bits, 1 byte.
typedef uint8_t byte;

const int JPEGSIZE = 512;

int main(int argc, char *argv[])
{
    int foundjpeg = 0;
    int jpegimagename = 0;
    int writingjpegdata = 0;

    //checks if the memory card exists.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //opens the memory card file.
    FILE *cardfile = fopen(argv[1], "r");
    //checks if the memory card is available to open on computer's memory.
    if (cardfile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    //creates a buffer to store bytes of jpeg images in memory card.
    byte jpegbytes[JPEGSIZE];
    //stores the patterns of every possible fourth byte of jpeg images in memory card.
    byte jpegfourthbytepatterns[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

    //creates a file for bytes of jpeg images in memory card to write into.
    FILE *jpegimagefile = NULL;
    //allocates memory for the string, the name of the recovered jpeg images.
    char *jpegimagenametext = malloc(sizeof(int) + 1);

    //reads and stores 512 bytes of jpeg images at a time until the end of the memory card.
    while (fread(jpegbytes, sizeof(byte), 512, cardfile))
    {
        //checks if a jpeg images is found in current 512 bytes.
        if (jpegbytes[0] == 0xff && jpegbytes[1] == 0xd8 && jpegbytes[2] == 0xff)
        {
            for (int i = 0; i < 16 ; i = i + 1)
            {
                if (jpegbytes[3] == jpegfourthbytepatterns[i])
                {
                    foundjpeg = 1;
                    i = 16;
                    if (writingjpegdata == 1)
                    {
                        //stops writing bytes to current file for bytes of jpeg images if another jpeg image is found in memory card.
                        fclose(jpegimagefile);
                        jpegimagename = jpegimagename + 1;
                    }
                }
            }
        }
        //if a jpeg image is found in current 512 bytes, write those 512 bytes into a file for bytes of jpeg images.
        if (foundjpeg == 1)
        {
            writingjpegdata = 1;
            if (jpegimagename < 10)
            {
                //jpegimagenametext = "000.jpg";
                sprintf(jpegimagenametext, "00%i.jpg", jpegimagename);
            }
            else if (jpegimagename < 100)
            {
                //jpegimagenametext = "001.jpg";
                sprintf(jpegimagenametext, "0%i.jpg", jpegimagename);
            }
            jpegimagefile = fopen(jpegimagenametext, "w");
            foundjpeg = 0;
        }
        if (writingjpegdata == 1)
        {
            fwrite(jpegbytes, sizeof(byte), 512, jpegimagefile);
        }
    }

    //close the memory card file after reading bytes.
    fclose(cardfile);
    //free up allocated space for the string, name of the recovered jpeg images.
    free(jpegimagenametext);

    return 0;
}