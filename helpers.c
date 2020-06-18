#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            
            double avg = (double)(b + g + r) / 3;
            
            int average = round(avg);
            
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            
            double sRed = .393 * r + .769 * g + .189 * b;
            double sGreen = .349 * r + .686 * g + .168 * b;
            double sBlue = .272 * r + .534 * g + .131 * b;
            
            int sepiaRed = round(sRed);
            int sepiaGreen = round(sGreen);
            int sepiaBlue = round(sBlue);
            
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE x = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = x;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)//top left corner
         {
                double avgB = (double)(img[i][j].rgbtBlue + img[i][j+1].rgbtBlue + img[i+1][j].rgbtBlue + img[i+1][j+1].rgbtBlue) / 4;

                double avgG = (double)(img[i][j].rgbtGreen + img[i][j+1].rgbtGreen + img[i+1][j].rgbtGreen + img[i+1][j+1].rgbtGreen) / 4;

                double avgR = (double)(img[i][j].rgbtRed + img[i][j+1].rgbtRed + img[i+1][j].rgbtRed + img[i+1][j+1].rgbtRed) / 4;

                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
            
        }
        else if (i == 0 && j == width - 1)//top right corner
        {
            
            double avgB = (double)(img[i][j-1].rgbtBlue + img[i][j].rgbtBlue + img[i+1][j-1].rgbtBlue + img[i+1][j].rgbtBlue) / 4;

            double avgG = (double)(img[i][j-1].rgbtGreen + img[i][j].rgbtGreen + img[i+1][j-1].rgbtGreen + img[i+1][j].rgbtGreen) / 4;

            double avgR = (double)(img[i][j-1].rgbtRed + img[i][j].rgbtRed + img[i+1][j-1].rgbtRed + img[i+1][j].rgbtRed) / 4;

            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
            
        }
        else if (i == height && j == 0)//bottom left corner
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i][j+1].rgbtBlue + img[i-1][j].rgbtBlue + img[i-1][j+1].rgbtBlue) / 4;

            double avgG = (double)(img[i][j].rgbtGreen + img[i][j+1].rgbtGreen+ img[i-1][j].rgbtGreen + img[i-1][j+1].rgbtGreen) / 4;

            double avgR = (double)(img[i][j].rgbtRed + img[i][j+1].rgbtRed + img[i-1][j].rgbtRed + img[i-1][j+1].rgbtRed) / 4;

            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
                
        }
        else if (i == height && j == width - 1)//bottom right corner
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i][j-1].rgbtBlue + img[i-1][j].rgbtBlue + img[i-1][j-1].rgbtBlue) / 4;

            double avgG = (double)(img[i][j].rgbtGreen + img[i][j-1].rgbtGreen + img[i-1][j].rgbtGreen + img[i-1][j-1].rgbtGreen) / 4;

            double avgR = (double)(img[i][j].rgbtRed + img[i][j-1].rgbtRed + img[i-1][j].rgbtRed + img[i-1][j-1].rgbtRed) / 4;

            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
    
        }
        else if (i == 0 && (j != 0 || j != width - 1))//top edge
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i][j-1].rgbtBlue + img[i][j+1].rgbtBlue + img[i+1][j-1].rgbtBlue + img[i+1][j].rgbtBlue + img[i+1][j+1].rgbtBlue) / 6;

            double avgG = (double)(img[i][j].rgbtGreen + img[i][j-1].rgbtGreen + img[i][j+1].rgbtGreen + img[i+1][j-1].rgbtGreen + img[i+1][j].rgbtGreen + img[i+1][j+1].rgbtGreen) / 6;

            double avgR = (double)(img[i][j].rgbtRed + img[i][j-1].rgbtRed + img[i][j+1].rgbtRed + img[i+1][j-1].rgbtRed + img[i+1][j].rgbtRed + img[i+1][j+1].rgbtRed) / 6;

                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (i == height && (j != 0 || j != width - 1))//bottom edge
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i][j-1].rgbtBlue + img[i][j+1].rgbtBlue + img[i-1][j-1].rgbtBlue + img[i-1][j].rgbtBlue + img[i-1][j+1].rgbtBlue) / 6;

            double avgG = (double)(img[i][j].rgbtGreen + img[i][j-1].rgbtGreen + img[i][j+1].rgbtGreen + img[i-1][j-1].rgbtGreen + img[i-1][j].rgbtGreen + img[i-1][j+1].rgbtGreen) / 6;

            double avgR = (double)(img[i][j].rgbtRed + img[i][j-1].rgbtRed + img[i][j+1].rgbtRed + img[i-1][j-1].rgbtRed + img[i-1][j].rgbtRed + img[i-1][j+1].rgbtRed) / 6;

                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (j == 0 && (i != 0 || i != height))//left edge
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i-1][j].rgbtBlue + img[i+1][j].rgbtBlue + img[i-1][j+1].rgbtBlue + img[i][j+1].rgbtBlue + img[i+1][j+1].rgbtBlue) / 6;

            double avgG = (double)(img[i][j].rgbtGreen + img[i-1][j].rgbtGreen + img[i+1][j].rgbtGreen + img[i-1][j+1].rgbtGreen + img[i][j+1].rgbtGreen + img[i+1][j+1].rgbtGreen) / 6;

            double avgR = (double)(img[i][j].rgbtRed + img[i-1][j].rgbtRed + img[i+1][j].rgbtRed + img[i-1][j+1].rgbtRed + img[i][j+1].rgbtRed + img[i+1][j+1].rgbtRed) / 6;

                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (j == width - 1 && (i != 0 || i != height))//right edge
        {
            double avgB = (double)(img[i][j].rgbtBlue + img[i-1][j].rgbtBlue + img[i+1][j].rgbtBlue + img[i-1][j-1].rgbtBlue + img[i][j-1].rgbtBlue + img[i+1][j-1].rgbtBlue) / 6;

            double avgG = (double)(img[i][j].rgbtGreen + img[i-1][j].rgbtGreen + img[i+1][j].rgbtGreen + img[i-1][j-1].rgbtGreen + img[i][j-1].rgbtGreen + img[i+1][j-1].rgbtGreen) / 6;

            double avgR = (double)(img[i][j].rgbtRed + img[i-1][j].rgbtRed + img[i+1][j].rgbtRed + img[i-1][j-1].rgbtRed + img[i][j-1].rgbtRed + img[i+1][j-1].rgbtRed) / 6;

                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else
        {
            double avgB = (double)(img[i-1][j-1].rgbtBlue + img[i-1][j].rgbtBlue + img[i-1][j+1].rgbtBlue + img[i][j-1].rgbtBlue + img[i][j].rgbtBlue + img[i][j+1].rgbtBlue + img[i+1][j-1].rgbtBlue + img[i+1][j].rgbtBlue + img[i+1][j+1].rgbtBlue) / 9;
                
            double avgG = (double)(img[i-1][j-1].rgbtGreen + img[i-1][j].rgbtGreen + img[i-1][j+1].rgbtGreen + img[i][j-1].rgbtGreen + img[i][j].rgbtGreen + img[i][j+1].rgbtGreen + img[i+1][j-1].rgbtGreen + img[i+1][j].rgbtGreen + img[i+1][j+1].rgbtGreen) / 9;
                
            double avgR = (double)(img[i-1][j-1].rgbtRed + img[i-1][j].rgbtRed + img[i-1][j+1].rgbtRed + img[i][j-1].rgbtRed + img[i][j].rgbtRed + img[i][j+1].rgbtRed + img[i+1][j-1].rgbtRed + img[i+1][j].rgbtRed + img[i+1][j+1].rgbtRed) / 9;

            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
            
        }
        }
    }
    return;
}
