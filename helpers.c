#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating the average of pixels
            int np = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //assigning the avg to all 3 colors
            image[i][j].rgbtBlue = np;
            image[i][j].rgbtGreen = np;
            image[i][j].rgbtRed = np;
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
            //calculating the formulas according to sepia
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            //if any of them is bigger than 255, making them 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //assigning values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swapping the right most part of picture with left most part
            int tRed = image[i][width - j - 1].rgbtRed;
            int tGreen = image[i][width - j - 1].rgbtGreen;
            int tBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = tRed;
            image[i][j].rgbtGreen = tGreen;
            image[i][j].rgbtBlue = tBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int aRed[height][width], aGreen[height][width], aBlue[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //if it is on the left top corner
            if (i == 0 && j == 0)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
            
                aGreen[i][j] = round((image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                      image[i][j].rgbtGreen) / 4.0);
            
                aBlue[i][j] = round((image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) /
                                    4.0); 
            }
            //if it is on the right top corner
            else if (i == 0 && j == width - 1)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
            
                aGreen[i][j] = round((image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                      image[i][j].rgbtGreen) / 4.0);
            
                aBlue[i][j] = round((image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                    4.0);
            }
            //if it is in the bottom left corner
            else if (i == height - 1 && j == 0)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
            
                aGreen[i][j] = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                      image[i][j].rgbtGreen) / 4.0);
            
                aBlue[i][j] = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) /
                                    4.0);
            }
            //if it is in the bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
            
                aGreen[i][j] = round((image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                      image[i][j].rgbtGreen) / 4.0);
            
                aBlue[i][j] = round((image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                    4.0);
            }
            //if it is on the top
            else if (i == 0)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i
                                    + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            
                aGreen[i][j] = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen
                                      + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
            
                aBlue[i][j] = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue
                                     + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //if it is at the bottom
            else if (i == height - 1)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i
                                    - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
            
                aGreen[i][j] = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                                      + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
            
                aBlue[i][j] = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                                     + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
            }
            //if it is at the left most part
            else if (j == 0)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                                    + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            
                aGreen[i][j] = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                                      + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
            
                aBlue[i][j] = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                                     + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //if it is right most part
            else if (j == width - 1)
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed
                                    + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
            
                aGreen[i][j] = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                                      + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
            
                aBlue[i][j] = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                                     + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
            }
            //if it is somewhere else where you can get 3 x 3 pixels
            else
            {
                //calculating average blur effect and storing them to color arrays
                aRed[i][j] = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed
                                    + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j +
                                            1].rgbtRed) / 9.0);
            
                aGreen[i][j] = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j -
                                      1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                      image[i + 1][j + 1].rgbtGreen) / 9.0);
            
                aBlue[i][j] = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j -
                                     1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i +
                                             1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //assigning values of blur arrays to our pixels
            image[i][j].rgbtRed = aRed[i][j];
            image[i][j].rgbtGreen = aGreen[i][j];
            image[i][j].rgbtBlue = aBlue[i][j];
        }
    }
    return;
}
