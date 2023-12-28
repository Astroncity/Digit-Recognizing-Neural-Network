#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "Linear Algebra/Matrix.h"
#include "Colors/colors.h"
#include "main.h"

#define IMAGEAMOUNT 60000

int main(int argc, char** argv){
    printColor("Hello World!\n", BOLDGREEN);
    int* labels = malloc(IMAGEAMOUNT * sizeof(int));
    Matrix* images = loadData("data/train.csv", labels);
    // print a few images
    printMatrix("Image", images[1]);
    printf("Label: %d\n", labels[1]);
    printImage(images[1]);

    free(images);
    free(labels);
    printRainbow("Finished.");
    return 0;
}

Matrix* loadData(char* filename, int* labelDest){
    FILE* file = fopen(filename, "r");

    int imageLen = 28 * 28;

    //! sizeof(Matrix) does not include the data array (flexible array), so we need to allocate that separately
    Matrix* images = malloc(sizeof(Matrix)* IMAGEAMOUNT + sizeof(double*) * IMAGEAMOUNT * imageLen);

    //? check if file exists
    if(file == NULL){
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }

    char* line = malloc(10000 * sizeof(char));
    int* labels = malloc(IMAGEAMOUNT * sizeof(int));

    int imageCount = 0;
    
    fscanf(file, "%s", line);
    fscanf(file, "%s", line);

    char* token;

    while(true){
        if(imageCount >= IMAGEAMOUNT){
            break;
        }

        token = strtok(line, ",");
        int label = (int)*token - '0';
        //printf("Label: %d\n", label);
        labels[imageCount] = label; 

        double** imageData = initMatrixData(1, imageLen);
        int column = 0;

        while(true){
            token = strtok(NULL, ",");

            if(token == NULL){
                break;
            }

            int pixel = atoi(token);
            imageData[0][column] = (double)pixel;
            column++;
        }

        Matrix image = initMatrix(1, imageLen, imageData);
        images[imageCount] = image;
        imageCount++;
        fscanf(file, "%s", line);
    }

    memcpy(labelDest, labels, IMAGEAMOUNT * sizeof(int));
    fclose(file);

    free(labels);
    free(token);
    free(line);

    return images;
}


double sigmoid(double x){
    return 1 / (1 + exp(-x));
}

double ReLU(double x){
    if(x < 0){
        return 0;
    }
    return x;
}



void printImage(Matrix image){
    FILE* file = fopen("image.txt", "w");
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            if(image.data[0][i * 28 + j] > 0){
                fprintf(file, "X");
            }else{
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
}