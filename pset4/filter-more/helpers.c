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
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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

// Blur image - Box Filter
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
                box[0] = copy[i - 1][j - 1];
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
                box[1] = copy[i - 1][j];
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
                box[2] = copy[i - 1][j + 1];
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
                box[3] = copy[i][j - 1];
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
                box[5] = copy[i][j + 1];
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
                box[6] = copy[i + 1][j - 1];
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
                box[7] = copy[i + 1][j];
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
                box[8] = copy[i + 1][j + 1];
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

// Detect edges - Sobel Operator
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Create kernels
    int Gx_k[9] = {-1, 0, 1,
                   -2, 0, 2,
                   -1, 0, 1};

    int Gy_k[9] = {-1, -2, -1,
                    0, 0, 0,
                    1, 2, 1};

    // Loop through image pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Build image filter box
            RGBTRIPLE t_left, t_center, t_right, c_left, c, c_right, b_left, b_center, b_right;

            // Top left
            if (i - 1 >= 0 && j - 1 >= 0)
                t_left = copy[i - 1][j - 1];
            else
            {
                t_left.rgbtRed = 0;
                t_left.rgbtGreen = 0;
                t_left.rgbtBlue = 0;
            }

            // Top center
            if (i - 1 >= 0 && j >= 0)
                t_center = copy[i - 1][j];
            else
            {
                t_center.rgbtRed = 0;
                t_center.rgbtGreen = 0;
                t_center.rgbtBlue = 0;
            }

            // Top Right
            if (i - 1 >= 0 && j + 1 < width)
                t_right = copy[i - 1][j + 1];
            else
            {
                t_right.rgbtRed = 0;
                t_right.rgbtGreen = 0;
                t_right.rgbtBlue = 0;
            }

            // Center left
            if (i >= 0 && j - 1 >= 0)
                c_left = copy[i][j - 1];
            else
            {
                c_left.rgbtRed = 0;
                c_left.rgbtGreen = 0;
                c_left.rgbtBlue = 0;
            }

            // Center
            if (i >= 0 && j >= 0)
                c = copy[i][j];
            else
            {
                c.rgbtRed = 0;
                c.rgbtGreen = 0;
                c.rgbtBlue = 0;
            }

            // Center right
            if (i >= 0 && j + 1 < width)
                c_right = copy[i][j + 1];
            else
            {
                c_right.rgbtRed = 0;
                c_right.rgbtGreen = 0;
                c_right.rgbtBlue = 0;
            }

            // Bottom left
            if (i + 1 < height && j - 1 >= 0)
                b_left = copy[i + 1][j - 1];
            else
            {
                b_left.rgbtRed = 0;
                b_left.rgbtGreen = 0;
                b_left.rgbtBlue = 0;
            }

            // Bottom center
            if (i + 1 < height && j >= 0)
                b_center = copy[i + 1][j];
            else
            {
                b_center.rgbtRed = 0;
                b_center.rgbtGreen = 0;
                b_center.rgbtBlue = 0;
            }

            // Bottom right
            if (i + 1 < height && j + 1 < width)
                b_right = copy[i + 1][j + 1];
            else
            {
                b_right.rgbtRed = 0;
                b_right.rgbtGreen = 0;
                b_right.rgbtBlue = 0;
            }

            // RGB Image Matrix
            int box[][3] = {{t_left.rgbtRed, t_left.rgbtGreen, t_left.rgbtBlue},
                            {t_center.rgbtRed, t_center.rgbtGreen, t_center.rgbtBlue},
                            {t_right.rgbtRed, t_right.rgbtGreen, t_right.rgbtBlue},
                            {c_left.rgbtRed, c_left.rgbtGreen, c_left.rgbtBlue},
                            {c.rgbtRed, c.rgbtGreen, c.rgbtBlue},
                            {c_right.rgbtRed, c_right.rgbtGreen, c_right.rgbtBlue},
                            {b_left.rgbtRed, b_left.rgbtGreen, b_left.rgbtBlue},
                            {b_center.rgbtRed, b_center.rgbtGreen, b_center.rgbtBlue},
                            {b_right.rgbtRed, b_right.rgbtGreen, b_right.rgbtBlue}};

            // Convolve image and sum
            int Gx[9][3], Gy[9][3], Gx_red = 0, Gx_green = 0, Gx_blue = 0, Gy_red = 0, Gy_green = 0,
                                    Gy_blue = 0;

            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    Gx[x][y] = box[x][y] * Gx_k[x];
                    Gy[x][y] = box[x][y] * Gy_k[x];
                    if (y == 0)
                    {
                        Gx_red += Gx[x][y];
                        Gy_red += Gy[x][y];
                    }
                    if (y == 1)
                    {
                        Gx_green += Gx[x][y];
                        Gy_green += Gy[x][y];
                    }
                    if (y == 2)
                    {
                        Gx_blue += Gx[x][y];
                        Gy_blue += Gy[x][y];
                    }
                }
            }

            // Combine Gx and Gy
            int sobel_filter_red = round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2)));
            int sobel_filter_green = round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2)));
            int sobel_filter_blue = round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2)));

            // Cap values at 255
            if (sobel_filter_red > 255)
                sobel_filter_red = 255;
            if (sobel_filter_green > 255)
                sobel_filter_green = 255;
            if (sobel_filter_blue > 255)
                sobel_filter_blue = 255;

            // Update pixel
            image[i][j].rgbtRed = sobel_filter_red;
            image[i][j].rgbtGreen = sobel_filter_green;
            image[i][j].rgbtBlue = sobel_filter_blue;
        }
    }
    return;
}
