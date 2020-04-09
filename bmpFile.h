#ifndef _BMP_FILE
#define _BMP_FILE
#include<stdio.h>
#include<stdlib.h>
#include"bmpStruct.h"
//这堆close就很难看，不该用这个词
int getBMP(BMP_FILE *bmp,char *path);
void closeImage(BMP_COLOR **image,int height);
BMP_COLOR** createImage(int height,int width,BMP_COLOR color);
void closeEnableLayer(int **enableLayer,int height);
void bmpFileMaker(BMP_FILE *bmp,char* fileName);
void closeBmp(BMP_FILE* bmp);
int** createEnableLayer(int height,int width);
BMP_FILE* createBMpFile(int height,int width,BMP_COLOR color);
#endif