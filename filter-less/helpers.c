#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double temp;
    for (int i = 0; i < height; i++)
    {
        for ( int j=0; j<width; j++) {
            temp = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/ (double)3;
            image[i][j].rgbtBlue = (BYTE) round(temp);
            image[i][j].rgbtGreen = (BYTE) round(temp);
            image[i][j].rgbtRed = (BYTE) round(temp);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double outRed, outGreen, outBlue;
    BYTE originalRed, originalGreen, originalBlue;
    for (int i = 0; i < height; i++)
    {
        for ( int j=0; j<width; j++) {
            outRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            outGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            outBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if (outRed >255) {
                image[i][j].rgbtRed = 255;
            } else image[i][j].rgbtRed = (BYTE) round(outRed);
            if (outGreen>255) {
                image[i][j].rgbtGreen = 255;
            } else image[i][j].rgbtGreen = (BYTE) round(outGreen);
            if (outBlue>255) {
                image[i][j].rgbtBlue = 255;
            } else image[i][j].rgbtBlue = (BYTE) round(outBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_temp)[width] = calloc(height,width * sizeof(RGBTRIPLE));
    memcpy (image_temp,image,height*width*sizeof(RGBTRIPLE));
    // *imagetemp = *image;

     for (int i = 0; i < height; i++)
    {

        for ( int j=0; j<width; j++) {
            image[i][j] = image_temp[i][width-1-j];
        }

    }
    free(image_temp);
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double red, blue, green, div_total;

    RGBTRIPLE(*image_temp)[width] = calloc(height,width * sizeof(RGBTRIPLE));
    memcpy (image_temp,image,height*width*sizeof(RGBTRIPLE));

     for (int i = 0; i < height; i++){
        for ( int j=0; j<width; j++) {
            red =0;
            blue=0;
            green=0;
            div_total=0;

            for (int x= i-1; x<=i+1; x++) {
                for (int y=j-1; y<=j+1; y++) {
                    if (x>=0 && x<height && y>=0 && y< width) {
                        red += image_temp[x][y].rgbtRed;
                        blue += image_temp[x][y].rgbtBlue;
                        green += image_temp[x][y].rgbtGreen;
                        div_total++;
                    }

                }
            }
            image[i][j].rgbtRed = (BYTE) round (red/div_total);
            image[i][j].rgbtBlue = (BYTE) round(blue/div_total);
            image[i][j].rgbtGreen = (BYTE) round(green/div_total);
        }
    }
    free(image_temp);
    return;
}
