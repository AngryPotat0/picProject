#include"kernal.h"
int kernal1[3][3] = {{-1,-1,0},{-1,0,1},{0,1,1}};//浮雕效果
int kernal2[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};//锐化效果
int kernal3[3][3] = {{0,0,0},{0,1,0},{0,0,0}};//useless
int kernal4[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};//边缘线
int kernal5[3][3] = {{0, -1, 0},{-1, 4, -1},{0, -1, 0}};//拉普拉斯核  边缘检测

int(*k1)[3] = kernal1;
int(*k2)[3] = kernal2;
int(*k3)[3] = kernal3;
int(*k4)[3] = kernal4;
int(*k5)[3] = kernal5;

BMP_COLOR **extendArray(BMP_COLOR **image,int height,int width,int extend)//图像数组 原数组高度 原数组宽度 扩展数量(暂时无用)
{
    BMP_COLOR **exImage = (BMP_COLOR**)malloc(sizeof(BMP_COLOR*) * (height + 2));
    int i = 0;
    exImage[i] = (BMP_COLOR*)malloc(sizeof(BMP_COLOR) * (width + 2));
    memset(exImage[i],0,(width + 2) * sizeof(BMP_COLOR));
    for(i = 1;i < height + 1;i++)
    {
        exImage[i] = (BMP_COLOR*)malloc(sizeof(BMP_COLOR) * (width + 2));
        memset(exImage[i],0,(width + 2) * sizeof(BMP_COLOR));//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        memcpy(exImage[i] + 1,image[i - 1],width * sizeof(BMP_COLOR));
    }
    //i++;
    exImage[i] = (BMP_COLOR*)malloc(sizeof(BMP_COLOR) * (width + 2));
    memset(exImage[i],0,(width + 2) * sizeof(BMP_COLOR));

    return exImage;

}

int matrix(COLOR **exImage,int(*kernal)[3],int y,int x,int type,int mod)//x y 为矩阵左上角坐标 type 决定rgb,
{
    int i,j;
    int sum = 0;
    if(type == 1)//blue
    {
        for(i = 0;i < 3;i++)
        {
            for(j = 0;j < 3;j++)
            {
                sum = sum + (int)exImage[i + y][j + x].blue * *(*(kernal + i) + j);
            }
        }
    }
    else if(type == 2)//green
    {
        for(i = 0;i < 3;i++)
        {
            for(j = 0;j < 3;j++)
            {
                sum = sum + (int)exImage[i + y][j + x].green * *(*(kernal + i) + j);
            }
        }
    }
    else//red
    {
        for(i = 0;i < 3;i++)
        {
            for(j = 0;j < 3;j++)
            {
                sum = sum + (int)exImage[i + y][j + x].red * *(*(kernal + i) + j);
            }
        }
    }
    //这一块的if确实丑陋，不过临时就这么写了，愚笨如我也写不出什么高质量代码。。。。。
    //这么写是不是错的啊。。。感觉就很诡异，虽然结果没毛病，嗯，看着似乎没毛病
    //不过这整个函数都挺丑陋的
    if(!mod)
    {
        if(sum < 0)return sum + 128;
        //if (sum > 255)return 255;
        return sum;
    }else{
        if(sum < 0)return 0;
        if (sum > 255)return 255;
        return sum;
    }
}

void closeExImage(COLOR **exImage,int height,int width)
{
    if(exImage)
    {
        int i;
        for(i = 0;i < height;i++)
        {
            free(exImage[i]);
        }
        free(exImage);
    }
}

void useKernal(BMP_FILE *bmp,int(*kernal)[3],int mod)
{
    BMP_COLOR **image = bmp->data.image;
    int height = bmp->picInfo.biHeight;
    int width = bmp->picInfo.biWidth;
    int **enbaleLayer = bmp->enableLayer;
    int i,j;
    COLOR **exImage = extendArray(image,height,width,0);
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            if(enbaleLayer[i][j] == 1)
            {
                image[i][j].blue = matrix(exImage,kernal,i,j,1,mod);
                image[i][j].green = matrix(exImage,kernal,i,j,2,mod);
                image[i][j].red = matrix(exImage,kernal,i,j,3,mod);
            }
        }
    }
    closeExImage(exImage,height + 2,width + 2);
}