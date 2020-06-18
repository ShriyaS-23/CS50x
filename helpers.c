#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            
            int average = round((b + g + r) / 3);
            
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
            
            int sepiaRed = .393 * r + .769 * g + .189 * b;
            int sepiaGreen = .349 * r + .686 * g + .168 * b;
            int sepiaBlue = .272 * r + .534 * g + .131 * b;
            
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
            image[i][j] = image[i][width - j];
            image[i][width - j] = x;
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
                int blue = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
                int avgB = blue/4;
                
                int green = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
                int avgG = blue/4;
                
                int red = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
                int avgR = red/4;
                
                image[i][j].rgbtBlue = avgB;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtRed = avgR;
            
        }
        else if (i == 0 && j == width - 1)//top right corner
        {
            
            int blue = image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue;
            int avgB = blue/4;
                
            int green = image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen;
            int avgG = green/4;
                
            int red = image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed;
            int avgR = red/4;
                
            image[i][j].rgbtBlue = avgB;
            image[i][j].rgbtGreen = avgG;
            image[i][j].rgbtRed = avgR;
            
        }
        else if (i == height && j == 0)//bottom left corner
        {
            int blue = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
            int avgB = blue/4;
                
            int green = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen+ image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
            int avgG = green/4;
            
            int red = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
            int avgR = red/4;
            
            image[i][j].rgbtBlue = avgB;
            image[i][j].rgbtGreen = avgG;
            image[i][j].rgbtRed = avgR;
                
        }
        else if (i == height && j == width - 1)//bottom right corner
        {
            int blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue;
            int avgB = blue/4;
                
            int green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen;
            int avgG = green/4;
                
            int red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed;
            int avgR = red/4;
            
            image[i][j].rgbtBlue = avgB;
            image[i][j].rgbtGreen = avgG;
            image[i][j].rgbtRed = avgR;
    
        }
        else if (i == 0 && (j != 0 || j != width - 1))//top edge
        {
            int blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
            int avgB = blue/6;
                
            int green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
            int avgG = green/6;
                
            int red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
            int avgR = red/6;
            
                image[i][j].rgbtBlue = avgB;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtRed = avgR;
        }
        else if (i == height && (j != 0 || j != width - 1))//bottom edge
        {
            int blue = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
            int avgB = blue/6;
                
            int green = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
            int avgG = green/6;
                
            int red = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
            int avgR = red/6;
            
                image[i][j].rgbtBlue = avgB;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtRed = avgR;
        }
        else if (j == 0 && (i != 0 || i != height))//left edge
        {
            int blue = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue;
            int avgB = blue/6;
                
            int green = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen;
            int avgG = green/6;
                
            int red = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed;
            int avgR = red/6;
            
                image[i][j].rgbtBlue = avgB;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtRed = avgR;
        }
        else if (j == width && (i != 0 || i != height))//right edge
        {
            int blue = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue;
            int avgB = blue/6;
                
            int green = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen;
            int avgG = green/6;
                
            int red = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed;
            int avgR = red/6;
            
                image[i][j].rgbtBlue = avgB;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtRed = avgR;
        }
        else if (i != 0 && i != height && j != 0 && j != width - 1)
        {
            int blue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
            int avgB = blue/9;
                
            int green = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
            int avgG = green/9;
                
            int red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
            int avgR = red/9;
            
            image[i][j].rgbtBlue = avgB;
            image[i][j].rgbtGreen = avgG;
            image[i][j].rgbtRed = avgR;
            
        }
        }
    }
    return;
}
