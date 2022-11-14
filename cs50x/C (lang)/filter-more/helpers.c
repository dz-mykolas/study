#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int newColor = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = newColor;
            image[i][j].rgbtGreen = newColor;
            image[i][j].rgbtBlue = newColor;
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
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // New image
    RGBTRIPLE new[height][width];

    // Loop through original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take coordinates of near pixels
            // Later check if in boundaries of image matrix
            int yCoords[] = {i - 1, i, i + 1};
            int xCoords[] = {j - 1, j, j + 1};

            // 3 ints for Red Green Blue values/count for average (division)
            int count = 0;
            int newR = 0, newG = 0, newB = 0;

            // Loops through temp coordinates
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    // Checks if in boundaries
                    if ((yCoords[y] >= 0 && yCoords[y] < height) &&
                        (xCoords[x] >= 0 && xCoords[x] < width))
                    {
                        // Adds 4, 6 or 9 pixels to colors in total
                        newR += image[yCoords[y]][xCoords[x]].rgbtRed;
                        newG += image[yCoords[y]][xCoords[x]].rgbtGreen;
                        newB += image[yCoords[y]][xCoords[x]].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculates new average color
            RGBTRIPLE newColor =
            {
                .rgbtRed = round(newR / (float)count),
                .rgbtGreen = round(newG / (float)count),
                .rgbtBlue = round(newB / (float)count)
            };
            new[i][j] = newColor;
        }
    }

    // Update here with new image to prevent taking already blurred pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new[i][j];
        }
    }
    return;
}

int cap(int x)
{
    if (x > 255)
    {
        return 255;
    }
    return x;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // New image
    RGBTRIPLE new[height][width];

    // Loop through original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GX[3][3] =
            {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
            };
            int GY[3][3] =
            {
                {-1, -2, -1},
                { 0,  0,  0},
                { 1,  2,  1}
            };

            // Take coordinates of near pixels
            // Later check if in boundaries of image matrix
            int yCoords[] = {i - 1, i, i + 1};
            int xCoords[] = {j - 1, j, j + 1};

            // 3 ints for Red Green Blue values/count for average (division)
            int newRx = 0, newGx = 0, newBx = 0;
            int newRy = 0, newGy = 0, newBy = 0;
            int count = 0;

            // Loops through temp coordinates
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    // Checks if in boundaries
                    if ((yCoords[y] >= 0 && yCoords[y] < height) &&
                        (xCoords[x] >= 0 && xCoords[x] < width))
                    {
                        newRx += image[yCoords[y]][xCoords[x]].rgbtRed * GX[y][x];
                        newGx += image[yCoords[y]][xCoords[x]].rgbtGreen * GX[y][x];
                        newBx += image[yCoords[y]][xCoords[x]].rgbtBlue * GX[y][x];

                        newRy += image[yCoords[y]][xCoords[x]].rgbtRed * GY[y][x];
                        newGy += image[yCoords[y]][xCoords[x]].rgbtGreen * GY[y][x];
                        newBy += image[yCoords[y]][xCoords[x]].rgbtBlue * GY[y][x];
                        count++;
                    }
                }
            }

            RGBTRIPLE newColor =
            {
                .rgbtRed = cap(round(sqrt((newRx * newRx) + (newRy * newRy)))),
                .rgbtGreen = cap(round(sqrt((newGx * newGx) + (newGy * newGy)))),
                .rgbtBlue = cap(round(sqrt((newBx * newBx) + (newBy * newBy))))
            };
            new[i][j] = newColor;
        }
    }
    // Update here with new image to prevent taking already changed pixels
    for (int i = 0; i < height; i++)
    {unzip recover.zip
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new[i][j];
        }
    }
    return;
}