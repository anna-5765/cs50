#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average RGB value of pixel
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen
                        + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute Sepia color
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Check if any new values are greater than 255 and cap
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            // Update pixel values
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
    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Build box
    int counter;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if pixels of box filter exist and add to array
            RGBTRIPLE box[9];
            counter = 0;
            
            // Top left corner
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                box[0] = copy[i-1][j-1];
                counter += 1;
            }
            else
            {
                box[0].rgbtRed = 0;
                box[0].rgbtGreen = 0;
                box[0].rgbtBlue = 0;
            }

            // Top edge
            if (i - 1 >= 0 && j >= 0)
            {
                box[1] = copy[i-1][j];
                counter += 1;
            }
            else
            {
                box[1].rgbtRed = 0;
                box[1].rgbtGreen = 0;
                box[1].rgbtBlue = 0;
            }

            // Top right corner
            if (i - 1 >= 0 && j + 1 < width)
            {
                box[2] = copy[i-1][j+1];
                counter += 1;
            }
            else
            {
                box[2].rgbtRed = 0;
                box[2].rgbtGreen = 0;
                box[2].rgbtBlue = 0;
            }

            // Left edge
            if (i >= 0 && j - 1 >= 0)
            {
                box[3] = copy[i][j-1];
                counter += 1;
            }
            else
            {
                box[3].rgbtRed = 0;
                box[3].rgbtGreen = 0;
                box[3].rgbtBlue = 0;
            }

            // Center
            if (i >= 0 && j >= 0)
            {
                box[4] = copy[i][j];
                counter += 1;
            }
            else
            {
                box[4].rgbtRed = 0;
                box[4].rgbtGreen = 0;
                box[4].rgbtBlue = 0;
            }

            // Right edge
            if (i >= 0 && j + 1 < width)
            {
                box[5] = copy[i][j+1];
                counter += 1;
            }
            else
            {
                box[5].rgbtRed = 0;
                box[5].rgbtGreen = 0;
                box[5].rgbtBlue = 0;
            }

            // Bottom left corner
            if (i + 1 < height && j - 1 >= 0)
            {
                box[6] = copy[i+1][j-1];
                counter += 1;
            }
            else
            {
                box[6].rgbtRed = 0;
                box[6].rgbtGreen = 0;
                box[6].rgbtBlue = 0;
            }

            // Bottom edge
            if (i + 1 < height && j >= 0)
            {
                box[7] = copy[i+1][j];
                counter += 1;
            }
            else
            {
                box[7].rgbtRed = 0;
                box[7].rgbtGreen = 0;
                box[7].rgbtBlue = 0;
            }

            // Bottom right corner
            if (i + 1 < height && j + 1 < width)
            {
                box[8] = copy[i+1][j+1];
                counter += 1;
            }
            else
            {
                box[8].rgbtRed = 0;
                box[8].rgbtGreen = 0;
                box[8].rgbtBlue = 0;
            }

            // Average RGB values & blur image
            float red = 0, green = 0, blue = 0;
            for (int k = 0; k < 9; k++)
            {
                red += box[k].rgbtRed;
                green += box[k].rgbtGreen;
                blue += box[k].rgbtBlue;
            }

            int av_red = round(red / counter);
            int av_green = round(green / counter);
            int av_blue = round(blue / counter);

            // Update pixel
            image[i][j].rgbtRed = av_red;
            image[i][j].rgbtGreen = av_green;
            image[i][j].rgbtBlue = av_blue;
        }
    }
    return;
}
