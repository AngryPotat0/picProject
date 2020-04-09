#include<stdio.h>
#include"bmpFile.h"
#include"kernal.h"
#include"photoshop.h"
int main()
{
    char defPath[50];
    char path[50];
    printf("pleash input path of image:\n");
    scanf("%s",&defPath);
    // printf("pleash input path of image:\n");
    // scanf("%s",&path);

    BMP_FILE *bmp = (BMP_FILE*)malloc(sizeof(BMP_FILE));
    int k = getBMP(bmp,defPath);
    useKernal(bmp,k1,0);
    bmpFileMaker(bmp,"red.bmp");
    closeBmp(bmp);
    // BMP_FILE *bbp = (BMP_FILE*)malloc(sizeof(BMP_FILE));
    // int k = getBMP(bmp,defPath);
    // int k1 = getBMP(bbp,path);

    // if(!k || !k1)printf("error");
    // else
    // {
    //     BMP_COLOR color = {0,255,0};
    //     //gcc main.c bmpFile.c kernal.c photoshop.c queue.c stack.c -o main.exe
    //     squareChose(bmp,0,0,100,100,1);
    //     //magicTool(bmp,10,10,5,1);
    //     fillColor(bmp,0,0,color);
    //     BMP_FILE* copy = copyImage(bmp);
    //     pasteImage(bbp,copy,0,0);
    //     bmpFileMaker(bbp,"bbp.bmp");
    //     bmpFileMaker(bmp,"red.bmp");
    //     closeBmp(copy);
    // }
    // closeBmp(bmp);
    // closeBmp(bbp);
    printf("over\n");
    return 0;
}