#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])

{
    float avg;
    for(int i=0;i<height;i++) // loop thru rows top to bottom
{
for(int j=0;j<width;j++) // loop thru columns left to right
{
   avg=round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.00));

image[i][j].rgbtRed=avg;
image[i][j].rgbtBlue=avg;
image[i][j].rgbtGreen=avg;
 }

}
}

// hit max limit
int limit(int rgb)
  {
if(rgb>255)
{
    rgb=255;
}
return rgb;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
for(int i=0;i<height;i++) // loop thru rows top to bottom
{
for(int j=0;j<width;j++) // loop thru columns left to right
{ int sepiaRed,sepiaGreen,sepiaBlue;

sepiaRed =limit( round (.393 *image[i][j].rgbtRed  + .769 *image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue));
  sepiaGreen =limit(round (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
  sepiaBlue = limit(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));
  
    image[i][j].rgbtRed=sepiaRed;
image[i][j].rgbtBlue=sepiaBlue;
image[i][j].rgbtGreen=sepiaGreen;
}
}
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{ RGBTRIPLE t;

    for(int i=0;i<height;i++) // loop thru rows top to bottom
{
    int n=(width);
    for(int j = 0; j <n/2; j++) // loop thru columns left to right until mid column
 {
     {
         int k=n-j; // last pixel-j gives the loop of pixels from right to mid column
      { // alterate :t=image[i][j];
     // image[i][j]=image[i][k-1];
      //image[i][k-1]=t;
        t[0]=image[i][j].rgbtRed;
    t[1]=image[i][j].rgbtGreen;
    t[2]=image[i][j].rgbtBlue;

    image[i][j].rgbtRed= image[i][k-1].rgbtRed;
    image[i][j].rgbtGreen= image[i][k-1].rgbtGreen;
    image[i][j].rgbtBlue= image[i][k-1].rgbtBlue;

   image[i][k-1].rgbtRed=t[0];
  image[i][k-1].rgbtGreen=t[1];
  image[i][k-1].rgbtBlue=t[2];
    
  }
 }
}
}
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int sumblue;
    int sumgreen;
    int sumred;
    float counter;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
           for(int m=-1;m<2;m++)  // loop thru row of pixel matrix 3x3 -1 0 1
           {
               for(int n=-1;n<2;n++) // loop thru column of pixel matrix 3x3 -1 0 1
          {
              if(i+m<0 || i+m>height-1) // to eliminate edges beyond the image above or bottom, if i=0 m=-1 then eliminate
           { continue; // like a break statement, moves to next iteration
           }
           if(j+n<0 || j+m>width-1) // to elimiate pixels beyond left and right boundary of image width
           { continue;
           } // the pixels which lie in image matrix will be added per rgb values
           sumblue+=image[i+m][j+n].rgbtBlue; // sum of blue values of all pixels in 3x3 for that particular pixel looped into m,n and then i,j
           sumgreen+=image[i+m][j+n].rgbtGreen;
           sumred+=image[i+m][j+n].rgbtRed;
           counter++; // after the rbg values of that particular pixel is added(adding for neighboring values of it) increase counter  and move to next m,n and then i,j


    // take avg by sum/ counter and store it in temp rgbtriple
    temp[i][j].rgbtBlue=round(sumblue/counter);
    temp[i][j].rgbtGreen=round(sumgreen/counter);
    temp[i][j].rgbtRed=round(sumred/counter);
          }
           }
        }
    } // we take a copy in temp so that the values for imageIJ dont change as loop proceeds
    // copy that into actual pixel for every pixel from all values of i and j
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
     image[i][j].rgbtBlue=temp[i][j].rgbtBlue;
     image[i][j].rgbtGreen=temp[i][j].rgbtGreen;
     image[i][j].rgbtRed=temp[i][j].rgbtRed;
        }
    }
}