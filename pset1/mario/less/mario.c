#include<cs50.h>
#include<stdio.h>

void printpyramid(int pyramidheight);

int main(void)
{
    int height;

    //ask user for height between 1 to 8 to print pyramid.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //printf("Stored: %i\n",height);


    printpyramid(height);
}

//prints pyramid based on height.
void printpyramid(int pyramidheight)
{
    //prints a row of the pyramid.
    for (int i = 0; i < pyramidheight; i = i + 1)
    {
        /*for(int j=0;j<i;j=j+1){
            printf("#");
        }*/
        /*for(int d=pyramidheight-1;d>i;d=d-1){
            printf(".");
        }*/

        //adds space(s) to a row of the pyramid while printing.
        for (int s = pyramidheight - 1; s > i; s = s - 1)
        {
            printf(" ");
        }

        //adds hashes(s) to a row of the pyramid while printing.
        for (int h = 0; h <= i; h = h + 1)
        {
            printf("#");
        }

        //adds next line to a row of the pyramid while printing.
        printf("\n");
    }
}