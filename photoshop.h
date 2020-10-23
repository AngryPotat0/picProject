#ifndef _PHOTOSHOP
#define _PHOTOSHOP
#include"bmpStruct.h"
#include"bmpFile.h"
#include"dataStruct.h"
#include"queue.h"
#include"stack.h"
#include<string.h>
#include<math.h>
BYTE **getGrayPicture(BMP_COLOR **Image,int height,int width);
void deleteGrayImage(BYTE **grayImage,int height);
int **CreateVisited(int height,int width);
void deleteVisited(int **visited,int height);
void magicTool(BMP_FILE *bmp,int y,int x,int range,int shift);
void fillColor(BMP_FILE *bmp,int y,int x,BMP_COLOR color);
void squareChose(BMP_FILE *bmp,int y1,int x1,int y2,int x2,int shift);
void Inverse(BMP_FILE *bmp);
BMP_FILE* copyImage(BMP_FILE *bmp);//复制一个图片之前要free之前复制的图片
void pasteImage(BMP_FILE* bmp,BMP_FILE* copy,int y,int x);
void drawLine(BMP_FILE *bmp,int x1,int y1,int x2,int y2);
void drawCircle(BMP_FILE *bmp,int x,int y,int r);
#endif