#include"bmpFile.h"
#include<string.h>
BMP_FILE* openBmp(char *path)//读取fp中数据，放入bf中,成功返回1，失败返回0 ,getBmp
{
    BMP_FILE *bmp = (BMP_FILE*)malloc(sizeof(BMP_FILE));
    if(bmp == NULL)
        return NULL;

    FILE* fp = fopen(path,"rb");
    if(!fp) return 0;
    fseek(fp,0,0);
    fread(&(bmp->head),sizeof(BMP_HEADER) - 2,1,fp);
    fseek(fp,sizeof(BMP_HEADER) - 2,0);
    fread(&(bmp->picInfo),sizeof(BMP_INFOHEAD),1,fp);
    fseek(fp,sizeof(BMP_HEADER) - 2 + sizeof(BMP_INFOHEAD),0);
    
    int i;//循环变量
    int bpp = (bmp->picInfo).biBitCount;//bits of each pixel
    int rowLength = (bmp->picInfo).biWidth * bpp / 8;
    int picHeight = (bmp->picInfo).biHeight;
    if(bpp != 24){fclose(fp); return 0;}

    (bmp->data).skip = 0;
    if(rowLength % 4 != 0)
    {
        (bmp->data).skip = ((rowLength / 4) + 1) * 4 - rowLength;
    }

    BMP_COLOR **image = (BMP_COLOR**)malloc(sizeof(BMP_COLOR*) * picHeight);//指向图片数据的二重指针
    for(i = 0;i < picHeight;i++)
    {
        image[i] = (BMP_COLOR*)malloc(rowLength);
        fseek(fp,sizeof(BMP_HEADER) - 2 + sizeof(BMP_INFOHEAD) + i * (rowLength + (bmp->data).skip),0);
        fread(image[i],rowLength,1,fp);
    }
//set enableLayer
    // int** enableLayer = (int**)malloc(sizeof(int*) * picHeight);
    // for(i = 0;i < picHeight;i++)
    // {
    //     enableLayer[i] = (int*)malloc(sizeof(int) * (bmp->picInfo).biWidth);
    //     memset(enableLayer[i],0,sizeof(int) * (bmp->picInfo).biWidth);
    // }

    bmp->enableLayer = createEnableLayer(picHeight,(bmp->picInfo).biWidth);
    (bmp->data).image = image;
    fclose(fp);
    return bmp;
}

void saveBmp(BMP_FILE *bmp,char* fileName)//生成bmp文件,bmpFileMaker
{
    BMP_HEADER head = bmp->head;
    BMP_INFOHEAD picInfo = bmp->picInfo;
    BMP_COLOR **image = (bmp->data).image;
    int skip = (bmp->data).skip;
    FILE *nf = fopen(fileName,"wb");
    fseek(nf,0,0);
    fwrite(&head,sizeof(BMP_HEADER) - 2,1,nf);
    fseek(nf,sizeof(BMP_HEADER) - 2,0);
    fwrite(&picInfo,sizeof(BMP_INFOHEAD),1,nf);
    fseek(nf,sizeof(BMP_HEADER) - 2 + sizeof(BMP_INFOHEAD),0);

    int i = 0;
    int j = 0;int k = 0;
    char skipword = 0;
    for(;i < picInfo.biHeight;i++)
    {
        for(j = 0;j <picInfo.biWidth;j++)
        {
            fprintf(nf,"%c%c%c",image[i][j].blue,image[i][j].green,image[i][j].red);
        }
        for(k = 0;k < skip;k++) fprintf(nf,"%c",skipword);

    }
    // closeBmp((bmp->data).image,(bmp->picInfo).biHeight);
    // closeEnableLayer(bmp->enableLayer,(bmp->picInfo).biHeight);
    fclose(nf);

}

BMP_COLOR** createImage(int height,int width,BMP_COLOR color)//创建一个图片（bmp文件中的图片数据部分）
{
    BMP_COLOR** Image = (BMP_COLOR**)malloc(sizeof(BMP_COLOR*) * height);
    for(int i = 0;i < height;i++)
    {
        Image[i] = (BMP_COLOR*)malloc(sizeof(BMP_COLOR) * width);
        for(int j = 0;j < width;j++)
        {
            Image[i][j] = color;
        }
    }
    return Image;
}

void closeImage(BMP_COLOR **image,int height)
{
    int i = 0;
    for(;i < height;i++)
        free(image[i]);
    free(image);
}

//控制层的创建函数，enableLayer控制诸如复制，粘贴，魔棒工具，油漆桶工具的作用范围
int** createEnableLayer(int height,int width)
{
    int** enableLayer = (int**)malloc(sizeof(int*) * height);
    for(int i = 0;i < height;i++)
    {
        enableLayer[i] = (int*)malloc(sizeof(int) * width);
        memset(enableLayer[i],0,sizeof(int) * width);
    }
    return enableLayer;
}

void eraseEnableLayer(int **enableLayer,int height,int width)//enableLayer重置为0，不删除
{
    int i,j;
    for(int i = 0;i < height;i++)
    {
        memset(enableLayer[i],0,sizeof(int) * width);
    }
}

void closeEnableLayer(int **enableLayer,int height)
{
    if(enableLayer == NULL)
        return;
    int i = 0;
    for(;i < height;i++)
        free(enableLayer[i]);
    free(enableLayer);
}

//释放bmp文件指针所拥有的内存
void closeBmp(BMP_FILE* bmp)
{
    closeImage(bmp->data.image,bmp->picInfo.biHeight);
    closeEnableLayer(bmp->enableLayer,bmp->picInfo.biHeight);
    free(bmp);
}

BMP_FILE* createBmpFile(int height,int width,BMP_COLOR color)
{//FIXME:
    BMP_FILE *bmp;
    bmp->head.bfType = 0x4d42;
    bmp->picInfo.biHeight = height;
    bmp->picInfo.biWidth = width;

    bmp->data.image = createImage(height,width,color);
    bmp->enableLayer = createEnableLayer(height,width);
    return bmp;
}