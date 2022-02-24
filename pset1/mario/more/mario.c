#include<cs50.h>
#include<stdio.h>

void printpyramid(int pyramidheight);

int main(void)
{
    int height;

    //asks user for height between 1 to 8 and asks again if height is less and 1 or greater than 8.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //prints the pyramid based on height that the user has typed in.
    printpyramid(height);
}

void printpyramid(int pyramidheight)
{
    //prints a row of the pyramid based on height.
    for (int i = 0; i < pyramidheight; i = i + 1)
    {
        /*for(int j=0;j<=i;j=j+1){
            printf("#");
        }*/

        //adds a space([-]) while printing a row.
        for (int s = pyramidheight - 1; s > i; s = s - 1)
        {
            //printf(".");
            printf(" ");
        }

        //adds a hash(#) for the left side pyramid while printing a row.
        for (int l = 0; l <= i; l = l + 1)
        {
            printf("#");
        }

        //printf("..");

        //adds two spaces("[-][-]") while printing a row.
        printf("  ");

        //adds a hash(#) for the right side pyramid while printing a row.
        for (int r = 0; r <= i; r = r + 1)
        {
            printf("#");
        }

        //adds a new line("\n") to end a row.
        printf("\n");
    }
}