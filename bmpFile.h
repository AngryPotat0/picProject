#ifndef _BMP_FILE
#define _BMP_FILE
#include<stdio.h>
#include<stdlib.h>
#include"bmpStruct.h"
//这堆close就很难看，不该用这个词
BMP_FILE* openBmp(char *path);
void closeBmp(BMP_FILE* bmp);
void closeImage(BMP_COLOR **image,int height);
BMP_COLOR** createImage(int height,int width,BMP_COLOR color);
void saveBmp(BMP_FILE *bmp,char* fileName);
int** createEnableLayer(int height,int width);
void eraseEnableLayer(int **enableLayer,int height,int width);
void closeEnableLayer(int **enableLayer,int height);
BMP_FILE* createBMpFile(int height,int width,BMP_COLOR color);
#endif