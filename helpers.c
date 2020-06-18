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
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)//top left corner
         {
                double blue = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
                double avgB = blue/4;
                
                double green = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
                double avgG = blue/4;
                
                double red = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
                double avgR = red/4;
                
                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
            
        }
        else if (i == 0 && j == width - 1)//top right corner
        {
            
            double blue = image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue;
            double avgB = blue/4;
                
            double green = image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen;
            double avgG = green/4;
                
            double red = image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed;
            double avgR = red/4;
                
            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
            
        }
        else if (i == height && j == 0)//bottom left corner
        {
            double blue = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
            double avgB = blue/4;
                
            double green = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen+ image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
            double avgG = green/4;
            
            double red = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
            double avgR = red/4;
            
            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
                
        }
        else if (i == height && j == width - 1)//bottom right corner
        {
            double blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue;
            double avgB = blue/4;
                
            double green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen;
            double avgG = green/4;
                
            double red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed;
            double avgR = red/4;
            
            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
    
        }
        else if (i == 0 && (j != 0 || j != width - 1))//top edge
        {
            double blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
            double avgB = blue/6;
                
            double green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
            double avgG = green/6;
                
            double red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
            double avgR = red/6;
            
                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (i == height && (j != 0 || j != width - 1))//bottom edge
        {
            double blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
            double avgB = blue/6;
                
            double green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
            double avgG = green/6;
                
            double red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
            double avgR = red/6;
            
                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (j == 0 && (i != 0 || i != height))//left edge
        {
            double blue = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue;
            double avgB = blue/6;
                
            double green = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen;
            double avgG = green/6;
                
            double red = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed;
            double avgR = red/6;
            
                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else if (j == width && (i != 0 || i != height))//right edge
        {
            double blue = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue;
            double avgB = blue/6;
                
            double green = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen;
            double avgG = green/6;
                
            double red = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed;
            double avgR = red/6;
            
                image[i][j].rgbtBlue = round(avgB);
                image[i][j].rgbtGreen = round(avgG);
                image[i][j].rgbtRed = round(avgR);
        }
        else
        {
            double blue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
            double avgB = blue/9;
                
            double green = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
            double avgG = green/9;
                
            double red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
            double avgR = red/9;
            
            image[i][j].rgbtBlue = round(avgB);
            image[i][j].rgbtGreen = round(avgG);
            image[i][j].rgbtRed = round(avgR);
            
        }
        }
    }
    return;
}
