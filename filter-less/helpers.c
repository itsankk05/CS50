#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.00;
            int avg = round(average);
            if(avg > 255){
                avg = 255;
            }
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
                }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue) ;
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue) ;
            if(sepiaRed > 255){
                sepiaRed = 255;
            }
            if(sepiaGreen > 255){
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255){
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            tmp[i][j] = image[i][width-j-1];
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int newRed = 0;
            int newGreen = 0;
            int newBlue = 0;
            float counter = 0.00;

            for(int k = -1; k < 2; k++){
                for(int l = -1; l < 2; l++){
                    if(i+k < 0 || i+k > height-1 || l+j < 0 || l+j > width-1){
                        continue;
                    }
                    newRed += image[i+k][j+l].rgbtRed;
                    newBlue += image[i+k][j+l].rgbtBlue;
                    newGreen += image[i+k][j+l].rgbtGreen;
                    counter++ ;
                }
            }
            temp[i][j].rgbtRed = round(newRed / counter);
            temp[i][j].rgbtBlue = round(newBlue / counter);
            temp[i][j].rgbtGreen = round(newGreen / counter);
        }
    }
    for(int y=0; y<height; y++){
        for(int z=0; z<width; z++){
            image[y][z].rgbtRed = temp[y][z].rgbtRed;
            image[y][z].rgbtBlue = temp[y][z].rgbtBlue;
            image[y][z].rgbtGreen = temp[y][z].rgbtGreen;
        }
    }
    return;
}
