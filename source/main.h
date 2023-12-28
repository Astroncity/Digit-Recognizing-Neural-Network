#ifndef MAIN
#define MAIN


Matrix* loadData(char* filename, int* labelDest);
double sigmoid(double x);
double ReLU(double x);
void printImage(Matrix image);
void printRainbow(char* str);

#endif