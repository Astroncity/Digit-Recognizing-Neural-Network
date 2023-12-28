#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void printColor(char* str, const char* color){
    printf(color);
    printf(str);
    printf(RESET);
    printf("\n");
}


void printRainbow(char* str){
    char* rainbow[] = {RED, BOLDRED, YELLOW, BOLDYELLOW, GREEN, BOLDGREEN, CYAN, BOLDCYAN, BLUE, BOLDBLUE, MAGENTA, BOLDMAGENTA};
    int rainbowLen = 12;
    int strLen = strlen(str);
    for(int i = 0; i < strLen; i++){
        printf(rainbow[i % rainbowLen]);
        printf("%c", str[i]);
    }
    printf(RESET);
    printf("\n");
}