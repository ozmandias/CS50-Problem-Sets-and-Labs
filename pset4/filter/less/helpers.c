#include "helpers.h"
#include<math.h>
#include<stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float averagepixels = 0;
    int grayscalepixels = 0;

    //printf("Blue:%i\nGreen:%i\nRed:%i\n",image[0][0].rgbtBlue,image[0][0].rgbtGreen,image[0][0].rgbtRed);

    //calculates grayscale for every pixel in the image.
    for (int i = 0; i < height; i = i + 1)
    {
        for (int j = 0; j < width; j = j + 1)
        {
            averagepixels = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3;
            grayscalepixels = round(averagepixels);
            image[i][j].rgbtBlue = grayscalepixels;
            image[i][j].rgbtGreen = grayscalepixels;
            image[i][j].rgbtRed = grayscalepixels;
        }
    }

    //printf("GrayscaleBlue:%i\nGrayscaleGreen:%i\nGrayscaleRed:%i\n",image[0][0].rgbtBlue,image[0][0].rgbtGreen,image[0][0].rgbtRed);

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiablue = 0;
    float sepiagreen = 0;
    float sepiared = 0;
    int sepiabluenumber = 0;
    int sepiagreennumber = 0;
    int sepiarednumber = 0;

    //calculates sepia color for every pixel in image.
    for (int i = 0; i < height; i = i + 1)
    {
        for (int j = 0; j < width; j = j + 1)
        {
            sepiablue = (0.272 * (float)image[i][j].rgbtRed) + (0.534 * (float)image[i][j].rgbtGreen) + (0.131 * (float)image[i][j].rgbtBlue);
            sepiagreen = (0.349 * (float)image[i][j].rgbtRed) + (0.686 * (float)image[i][j].rgbtGreen) + (0.168 * (float)image[i][j].rgbtBlue);
            sepiared = (0.393 * (float)image[i][j].rgbtRed) + (0.769 * (float)image[i][j].rgbtGreen) + (0.189 * (float)image[i][j].rgbtBlue);

            sepiabluenumber = round(sepiablue);
            sepiagreennumber = round(sepiagreen);
            sepiarednumber = round(sepiared);

            //sets color values in between minimum 0 and maximum 255.
            if (sepiabluenumber > 255)
            {
                sepiabluenumber = 255;
            }
            else if (sepiabluenumber < 0)
            {
                sepiabluenumber = 0;
            }
            if (sepiagreennumber > 255)
            {
                sepiagreennumber = 255;
            }
            else if (sepiagreennumber < 0)
            {
                sepiagreennumber = 0;
            }
            if (sepiarednumber > 255)
            {
                sepiarednumber = 255;
            }
            else if (sepiarednumber < 0)
            {
                sepiarednumber = 0;
            }

            image[i][j].rgbtBlue = sepiabluenumber;
            image[i][j].rgbtGreen = sepiagreennumber;
            image[i][j].rgbtRed = sepiarednumber;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixels[width];
    int reflectionstart = width - 1;

    //set every pixel in reverse order horizontally in the image.
    for (int i = 0; i < height; i = i + 1)
    {
        //stores every pixel in horizontal direction in the image.
        for (int j = 0; j < width; j = j + 1)
        {
            pixels[j].rgbtBlue = image[i][j].rgbtBlue;
            pixels[j].rgbtGreen = image[i][j].rgbtGreen;
            pixels[j].rgbtRed = image[i][j].rgbtRed;
        }
        //change the pixels in horizontal direction in the image to the reverse horizontal direction using the stored pixels.
        for (int p = 0; p < width; p = p + 1)
        {
            image[i][p].rgbtBlue = pixels[reflectionstart].rgbtBlue;
            image[i][p].rgbtGreen = pixels[reflectionstart].rgbtGreen;
            image[i][p].rgbtRed = pixels[reflectionstart].rgbtRed;
            reflectionstart = reflectionstart - 1;
        }
        reflectionstart = width - 1;
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurimage[height][width];
    float blurblue = 0;
    float blurgreen = 0;
    float blurred = 0;
    int pixelsinblur = 0;
    float averageblue = 0;
    float averagegreen = 0;
    float averagered = 0;
    int blurbluenumber = 0;
    int blurgreennumber = 0;
    int blurrednumber = 0;

    //for every pixel in the image, takes the original pixel and the surrounding pixels if they are in the boundary of the image.
    for (int i = 0; i < height; i = i + 1)
    {
        for (int j = 0; j < width; j = j + 1)
        {
            //i = 0;
            //j = 0;
            //printf("Takes original pixel\n");
            blurblue = (float)image[i][j].rgbtBlue;
            blurgreen = (float)image[i][j].rgbtGreen;
            blurred = (float)image[i][j].rgbtRed;
            pixelsinblur = pixelsinblur + 1;
            if (j > 0)
            {
                //printf("Takes left pixel\n");
                blurblue = (float)blurblue + (float)image[i][j - 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i][j - 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i][j - 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (j < width && j != width - 1)
            {
                //printf("Takes right pixel\n");
                blurblue = (float)blurblue + (float)image[i][j + 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i][j + 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i][j + 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i > 0)
            {
                //printf("Takes top pixel\n");
                blurblue = (float)blurblue + (float)image[i - 1][j].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i - 1][j].rgbtGreen;
                blurred = (float)blurred + (float)image[i - 1][j].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i > 0 && j > 0)
            {
                //printf("Takes top left pixel\n");
                blurblue = (float)blurblue + (float)image[i - 1][j - 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i - 1][j - 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i - 1][j - 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i > 0 && j < width && j != width - 1)
            {
                //printf("Takes top right pixel\n");
                blurblue = (float)blurblue + (float)image[i - 1][j + 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i - 1][j + 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i - 1][j + 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i < height && i != height - 1)
            {
                //printf("Takes bottom pixel\n");
                blurblue = (float)blurblue + (float)image[i + 1][j].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i + 1][j].rgbtGreen;
                blurred = (float)blurred + (float)image[i + 1][j].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i < height && i != height - 1 && j > 0)
            {
                //printf("Takes bottom left pixel\n");
                blurblue = (float)blurblue + (float)image[i + 1][j - 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i + 1][j - 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i + 1][j - 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            if (i < height && i != height - 1 && j < width && j != width - 1)
            {
                //printf("Takes bottom right pixel\n");
                blurblue = (float)blurblue + (float)image[i + 1][j + 1].rgbtBlue;
                blurgreen = (float)blurgreen + (float)image[i + 1][j + 1].rgbtGreen;
                blurred = (float)blurred + (float)image[i + 1][j + 1].rgbtRed;
                pixelsinblur = pixelsinblur + 1;
            }
            /*for(int v=i-1;v<=i+1;v=v+1){
                for(int h=j-1;h<=j+1;h=h+1){
                    if(v>=0&&v<height&&h>=0&&h<width){
                        blurblue = blurblue + (float)image[v][h].rgbtBlue;
                        blurgreen = blurgreen + (float)image[v][h].rgbtGreen;
                        blurred = blurred + (float)image[v][h].rgbtRed;
                        pixelsinblur = pixelsinblur+1;
                    }
                }
            }*/
            averageblue = (float)blurblue / pixelsinblur;
            averagegreen = (float)blurgreen / pixelsinblur;
            averagered = (float)blurred / pixelsinblur;

            blurbluenumber = round(averageblue);
            blurgreennumber = round(averagegreen);
            blurrednumber = round(averagered);

            //stores the color values of pixels as another image to avoid changing the original color values of the image.
            blurimage[i][j].rgbtBlue = blurbluenumber;
            blurimage[i][j].rgbtGreen = blurgreennumber;
            blurimage[i][j].rgbtRed = blurrednumber;

            blurblue = 0;
            blurgreen = 0;
            blurred = 0;
            pixelsinblur = 0;
        }
    }

    //copy the color values from another image to the original image.
    for (int h = 0; h < height; h = h + 1)
    {
        for (int w = 0; w < width; w = w + 1)
        {
            blurbluenumber = blurimage[h][w].rgbtBlue;
            blurgreennumber = blurimage[h][w].rgbtGreen;
            blurrednumber = blurimage[h][w].rgbtRed;
            image[h][w].rgbtBlue = blurbluenumber;
            image[h][w].rgbtGreen = blurgreennumber;
            image[h][w].rgbtRed = blurrednumber;
        }
    }
    return;
}
