#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int grey = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue)/3.00);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = grey;
           
        }
    }
\
}


int max(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            image[i][j].rgbtRed = max(round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue));
            image[i][j].rgbtGreen = max(round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue));
            image[i][j].rgbtBlue = max(round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue));
        }
            
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempr; 
    int tempg; 
    int tempb; 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tempr = image[i][j].rgbtRed;
            tempg = image[i][j].rgbtGreen;
            tempb = image[i][j].rgbtBlue;
            
            
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            
            image[i][width - j - 1].rgbtRed = tempr;
            image[i][width - j - 1].rgbtGreen = tempg;
            image[i][width - j - 1].rgbtBlue = tempb;
            
            
        
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ///////////            ///////////            ///////////            ///////////            ///////////
            int rvalue = 0;
            int gvalue = 0;
            int bvalue = 0;
            RGBTRIPLE blur;
            int values_present = 0;
            for (int ii = -1; ii <= 1; ii++)
            {
                for (int jj = -1; jj <= 1; jj++)
                {
                    int tempi = i + ii;
                    int tempj = j + jj;
                    if ( 0 <= tempi  && tempi < height && 0 <= tempj && tempj < width)
                    {
                        values_present++;
                        rvalue += image[tempi][tempj].rgbtRed;
                        gvalue += image[tempi][tempj].rgbtGreen;
                        bvalue += image[tempi][tempj].rgbtBlue;
                    }
                }
            }
            blur.rgbtRed = round((float) rvalue/values_present);
            blur.rgbtGreen = round((float) gvalue/values_present);
            blur.rgbtBlue = round((float) bvalue/values_present);
            tempimage[i][j] = blur;
            
        }
    }
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempimage[i][j];
        }
    }
    return;
}
