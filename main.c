#include<stdio.h>
#include"bmpFile.h"
#include"kernal.h"
#include"photoshop.h"
int main()
{
    char defPath[50];
    char path[50];
    BMP_COLOR color;
    printf("pleash input path of image:\n");
    scanf("%s",&defPath);
    // printf("input color,blue,green,red:\n");
    // scanf("%d",&color.blue);
    // scanf("%d",&color.green);
    // scanf("%d",&color.red);
    printf("pleash input path of image:\n");
    scanf("%s",&path);

    BMP_FILE *bmp = openBmp(defPath);
    BMP_FILE* bmp1 = openBmp(path);
    squareChose(bmp,0,0,100,100,0);
    BMP_FILE* copy = copyImage(bmp);
    pasteImage(bmp1,copy,0,0);
    closeBmp(copy);
    // useKernal(bmp,k5,1);
    // fillColor(bmp,10,10,color);
    // saveBmp(bmp,"reds.bmp");
    saveBmp(bmp1,"ans.bmp");
    closeBmp(bmp);
    closeBmp(bmp1);
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