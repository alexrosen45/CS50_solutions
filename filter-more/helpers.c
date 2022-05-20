#include "helpers.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // get RGB values
            double red = image[i][j].rgbtRed;
            double green = image[i][j].rgbtGreen;
            double blue = image[i][j].rgbtBlue;
            // average RGB values
            int avg = round((red+green+blue)/3);

            // add average values to image
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // reflect image using temp_pixel
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width/2; j++) {
            RGBTRIPLE temp_pixel = image[i][j];
            // replace value at i, j
            image[i][j] = image[i][width-(j+1)];
            // add value at i, j to replaced value place
            image[i][width-(j+1)] = temp_pixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create temp array
    RGBTRIPLE temp_image[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double red_sum = 0;
            double green_sum = 0;
            double blue_sum = 0;
            int count = 0;
            for (int k = -1; k < 2; k++) {
                if (i+k >= 0 && i+k <= height-1) {
                    for (int l = -1; l < 2; l++) {
                        if (j+l >= 0 && j+l <= width-1) {
                            red_sum += image[i+k][j+l].rgbtRed;
                            green_sum += image[i+k][j+l].rgbtGreen;
                            blue_sum += image[i+k][j+l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            temp_image[i][j].rgbtRed = round(red_sum/count);
            temp_image[i][j].rgbtGreen = round(green_sum/count);
            temp_image[i][j].rgbtBlue = round(blue_sum/count);
            // printf("red is %f\n", red_sum/count);
            // printf("green is %f\n", green_sum/count);
            // printf("blue is %f\n", blue_sum/count);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp_image[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create temp array
    RGBTRIPLE temp_image[height][width];

    // kernel arrays
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double red_sum_x = 0;
            double green_sum_x = 0;
            double blue_sum_x = 0;
            double red_sum_y = 0;
            double green_sum_y = 0;
            double blue_sum_y = 0;

            for (int k = -1; k < 2; k++) {
                if (i+k >= 0 && i+k <= height-1) {
                    for (int l = -1; l < 2; l++) {
                        if (j+l >= 0 && j+l <= width-1) {
                            red_sum_x += Gx[k+1][l+1]*image[i+k][j+l].rgbtRed;
                            green_sum_x += Gx[k+1][l+1]*image[i+k][j+l].rgbtGreen;
                            blue_sum_x += Gx[k+1][l+1]*image[i+k][j+l].rgbtBlue;

                            red_sum_y += Gy[k+1][l+1]*image[i+k][j+l].rgbtRed;
                            green_sum_y += Gy[k+1][l+1]*image[i+k][j+l].rgbtGreen;
                            blue_sum_y += Gy[k+1][l+1]*image[i+k][j+l].rgbtBlue;
                        }
                    }
                }
            }
            int red = round(sqrt((red_sum_x*red_sum_x)+(red_sum_y*red_sum_y)));
            int green = round(sqrt((green_sum_x*green_sum_x)+(green_sum_y*green_sum_y)));
            int blue = round(sqrt((blue_sum_x*blue_sum_x)+(blue_sum_y*blue_sum_y)));

            if (red > 255) {
                red = 255;
            }
            if (green > 255) {
                green = 255;
            }
            if (blue > 255) {
                blue = 255;
            }

            temp_image[i][j].rgbtRed = red;
            temp_image[i][j].rgbtGreen = green;
            temp_image[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp_image[i][j];
        }
    }
}
