#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double averageSum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int average = round(averageSum/3);
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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE tempTriple = image[i][j];
            image[i][j] = image[i][width - (j+1)];
            image[i][width - (j+1)] = tempTriple;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE og_image[height][width];
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            og_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumCount = 0;
            double R_averageSum = 0;
            double G_averageSum = 0;
            double B_averageSum = 0;
            int R_average;
            int G_average;
            int B_average;

            R_averageSum += og_image[i][j].rgbtRed;
            G_averageSum += og_image[i][j].rgbtGreen;
            B_averageSum += og_image[i][j].rgbtBlue;
            sumCount++;

            if (j - 1 >= 0)
            {
                R_averageSum += og_image[i][j-1].rgbtRed;
                G_averageSum += og_image[i][j-1].rgbtGreen;
                B_averageSum += og_image[i][j-1].rgbtBlue;
                sumCount++;
                if(i - 1 >= 0)
                {
                    R_averageSum += og_image[i-1][j-1].rgbtRed;
                    G_averageSum += og_image[i-1][j-1].rgbtGreen;
                    B_averageSum += og_image[i-1][j-1].rgbtBlue;
                    sumCount++;
                }
                if(i + 1 < height)
                {
                    R_averageSum += og_image[i+1][j-1].rgbtRed;
                    G_averageSum += og_image[i+1][j-1].rgbtGreen;
                    B_averageSum += og_image[i+1][j-1].rgbtBlue;
                    sumCount++;
                }
            }
            if (j + 1 < width)
            {
                R_averageSum += og_image[i][j+1].rgbtRed;
                G_averageSum += og_image[i][j+1].rgbtGreen;
                B_averageSum += og_image[i][j+1].rgbtBlue;
                sumCount++;

                if(i - 1 >= 0)
                {
                    R_averageSum += og_image[i-1][j+1].rgbtRed;
                    G_averageSum += og_image[i-1][j+1].rgbtGreen;
                    B_averageSum += og_image[i-1][j+1].rgbtBlue;
                    sumCount++;
                }
                if(i + 1 < height)
                {
                    R_averageSum += og_image[i+1][j+1].rgbtRed;
                    G_averageSum += og_image[i+1][j+1].rgbtGreen;
                    B_averageSum += og_image[i+1][j+1].rgbtBlue;
                    sumCount++;
                }
            }
            if (i - 1 >= 0)
            {
                R_averageSum += og_image[i-1][j].rgbtRed;
                G_averageSum += og_image[i-1][j].rgbtGreen;
                B_averageSum += og_image[i-1][j].rgbtBlue;
                sumCount++;
            }
            if (i + 1 < height)
            {
                R_averageSum += og_image[i+1][j].rgbtRed;
                G_averageSum += og_image[i+1][j].rgbtGreen;
                B_averageSum += og_image[i+1][j].rgbtBlue;
                sumCount++;
            }
            R_average = round(R_averageSum/sumCount);
            G_average = round(G_averageSum/sumCount);
            B_average = round(B_averageSum/sumCount);

            image[i][j].rgbtRed = R_average;
            image[i][j].rgbtGreen = G_average;
            image[i][j].rgbtBlue = B_average;
        }
    }

    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double red_GxValue = 0;
            double red_GyValue = 0;

            double green_GxValue = 0;
            double green_GyValue = 0;

            double blue_GxValue = 0;
            double blue_GyValue = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if ((h + (i-1) >= 0 && h + (i-1) < height) && (w + (j-1) >= 0 && w + (j-1) < width))
                    {
                        red_GxValue +=  (image[h + (i-1)][w + (j-1)].rgbtRed) * Gx[i][j];
                        green_GxValue +=  (image[h + (i-1)][w + (j-1)].rgbtGreen) * Gx[i][j];
                        blue_GxValue +=  (image[h + (i-1)][w + (j-1)].rgbtBlue) * Gx[i][j];

                        red_GyValue +=  (image[h + (i-1)][w + (j-1)].rgbtRed) * Gy[i][j];
                        green_GyValue +=  (image[h + (i-1)][w + (j-1)].rgbtGreen) * Gy[i][j];
                        blue_GyValue +=  (image[h + (i-1)][w + (j-1)].rgbtBlue) * Gy[i][j];
                    }
                }
            }

            int red_ChannelValue = round(sqrt(red_GxValue * red_GxValue + red_GyValue * red_GyValue));
            int green_ChannelValue = round(sqrt(green_GxValue * green_GxValue + green_GyValue * green_GyValue));
            int blue_ChannelValue = round(sqrt(blue_GxValue * blue_GxValue + blue_GyValue * blue_GyValue));

            if(red_ChannelValue > 255)
            {
                red_ChannelValue = 255;
            }
            if(green_ChannelValue > 255)
            {
                green_ChannelValue = 255;
            }
            if(blue_ChannelValue > 255)
            {
                blue_ChannelValue = 255;
            }

            temp[h][w].rgbtRed = red_ChannelValue;
            temp[h][w].rgbtGreen = green_ChannelValue;
            temp[h][w].rgbtBlue = blue_ChannelValue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
