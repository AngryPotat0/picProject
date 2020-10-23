#ifndef KERNAL
#define KERNAL
#include <string.h>
#include"bmpFile.h"
typedef BMP_COLOR COLOR;

extern int(*k1)[3];
extern int(*k2)[3];
extern int(*k3)[3];
extern int(*k4)[3];
extern int(*k5)[3];

// BMP_COLOR **extendArray(BMP_COLOR **image,int height,int width,int extend);
// int matrix(COLOR **exImage,int(*kernal)[3],int y,int x,int type,int mod);
// void closeExImage(COLOR **exImage,int height,int width);
void useKernal(BMP_FILE *bmp,int(*kernal)[3],int mod);



#endif