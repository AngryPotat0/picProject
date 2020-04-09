#include"photoshop.h"
// #define __PHOTOSHOP_DEBUG__
// #define __GRAYIMAGE_DEBUG__
#ifdef __PHOTOSHOP_DEBUG__
#include<stdio.h>
#endif
void changeYs(BMP_FILE *bmp,int* y1,int* y2)
{
    *y1 = bmp->picInfo.biHeight - *y1 - 1;
    *y2 = bmp->picInfo.biHeight - *y2 - 1;
}

void changeY(BMP_FILE *bmp,int* y)
{
    *y = bmp->picInfo.biHeight - *y - 1;
}

BYTE **getGrayPicture(BMP_COLOR **Image,int height,int width)
{
    BYTE **grayImage;
    grayImage = (BYTE**)malloc(sizeof(BYTE*) * height);
    int i,j;
    for(i = 0;i < height;i++)
    {
        grayImage[i] = (BYTE*)malloc(sizeof(BYTE) * width);
        for(j = 0;j < width;j++)
        {
            grayImage[i][j] = (Image[i][j].red * 299 + Image[i][j].green * 587 + Image[i][j].blue * 114 + 500) / 1000;
        }
    }
#ifdef __GRAYIMAGE_DEBUG__
    printf("grayimage is:\n");
    for(int i = 0;i < height;i++)
    {
        for(int j = 0;j < width;j++)
        {
            printf("%d ",grayImage[i][j]);
        }
        printf("\n");
    }
    printf("_____and done\n");
#endif
    return grayImage;
}

void deleteGrayImage(BYTE **grayImage,int height)
{
    int i = 0;
    for(;i < height;i++)
    {
        free(grayImage[i]);
    }
    free(grayImage);
}

void eraseEnableLayer(int **enableLayer,int height,int width)//enableLayer重置为0，不删除
{
    int i,j;
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            enableLayer[i][j] = 0;
        }
    }
}

int **CreateVisited(int height,int width)
{
    int **visited;
    visited = (int**)malloc(sizeof(int*) * (height + 2));
    int i = 0;
    visited[i] = (int*)malloc(sizeof(int) * (width + 2));
    memset(visited[i],1,sizeof(int) * (width + 2));//16843009??????????????????????????????????????????
    for(i = 1;i < height + 1;i++)
    {
        visited[i] = (int*)malloc(sizeof(int) * (width + 2));
        memset(visited[i],0,sizeof(int) * (width + 2));
        visited[i][0] = 1;
        visited[i][width + 1] = 1;
    }//初始化visited数组 数组用于判断某一个像素是否被访问过
    visited[i] = (int*)malloc(sizeof(int) * (width + 2));
    memset(visited[i],1,sizeof(int) * (width + 2));
    return visited;
}

void deleteVisited(int **visited,int height)
{
    for(int i = 0;i < height + 2;i++)
    {
        free(visited[i]);
    }
    free(visited);
}


void magicTool(BMP_FILE *bmp,int y,int x,int range,int shift)
{
#ifdef __PHOTOSHOP_DEBUG__
    printf("magic tool is working>>>>>\n");
#endif
    changeY(bmp,&y);
    int height = (bmp->picInfo).biHeight;
    int width = (bmp->picInfo).biWidth;
    int **enableLayer = bmp->enableLayer;
    BYTE **grayImage = getGrayPicture(bmp->data.image,height,width);
    if(!shift)eraseEnableLayer(enableLayer,height,width);
    int **visited = CreateVisited(height,width);
    Queue* queue = Create_Queue();
    int queueOverFlow = 0;
    elementType data,ndata;
    data.y = y;
    data.x = x;
    //image[y][x]:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    enableLayer[data.y][data.x] = 1;
    visited[data.y + 1][data.x + 1] = 1;
    queueOverFlow = queue_Push(queue,data);
    while (!queue_IsEmpty(queue))
    {
        data = queue_Pop(queue);
        //pushDataToQueue(data,grayImage,visited,height,width);
        for(int i = -1;i < 2;i++)
        {
            for(int j = -1;j < 2;j++)
            {
                if(i == 0 && j == 0)continue;
                ndata.x = data.x + i;
                ndata.y = data.y + j;
#ifdef __PHOTOSHOP_DEBUG__
    printf("check ndata %d %d\n",ndata.y,ndata.x);
#endif
                if(visited[ndata.y + 1][ndata.x + 1] == 0 && abs(grayImage[ndata.y][ndata.x] - grayImage[data.y][data.x]) < range)
                {
                    enableLayer[ndata.y][ndata.x] = 1;
                    queueOverFlow = queue_Push(queue,ndata);
                    visited[ndata.y + 1][ndata.x + 1] = 1;
                }
            }
        }

    }

    deleteGrayImage(grayImage,height);
    deleteVisited(visited,height);
}

void fillColor(BMP_FILE *bmp,int y,int x,BMP_COLOR color)
{
    changeY(bmp,&y);
    Queue *queue = Create_Queue();
    int **visited = CreateVisited((bmp->picInfo).biHeight,(bmp->picInfo).biWidth);
    elementType data,ndata;
    data.x = x;
    data.y = y;
    if((bmp->enableLayer)[y][x] == 0)return;
    int qovf = queue_Push(queue,data);
    visited[data.y + 1][data.x + 1] = 1;
    (bmp->data).image[data.y][data.x] = color;
    while(!queue_IsEmpty(queue))
    {
        //printf("in while\n");
        data = queue_Pop(queue);
        for(int i = -1;i < 2;i++)
        {
            for(int j = -1;j < 2;j++)
            {
                if(i == 0 && j == 0)continue;
                ndata.y = data.y + j;
                ndata.x = data.x + i;
                //printf("ok,code words fine,now i and j is %d %d\n",i,j);
                if(visited[ndata.y + 1][ndata.x + 1] == 0 && (bmp->enableLayer)[ndata.y][ndata.x] == 1)
                {
                    //printf("into if\n");
                    visited[ndata.y + 1][ndata.x + 1] = 1;
                    queue_Push(queue,ndata);
                    (bmp->data).image[ndata.y][ndata.x] = color;
                }
            }
        }
    }
    
    deleteVisited(visited,(bmp->picInfo).biHeight);
}
//shift:矩形选框之前是否清除之前选择区域，1：不清除 0：清除
void squareChose(BMP_FILE *bmp,int y1,int x1,int y2,int x2,int shift)//TODO: fix this
{//矩形左上角坐标，右下角坐标（正常图片中
printf("In to squareChose\n");
    if(!shift)eraseEnableLayer(bmp->enableLayer,(bmp->picInfo).biHeight,(bmp->picInfo).biWidth);
    int** enableLayer = bmp->enableLayer;
    changeYs(bmp,&y1,&y2);
    printf("Now in squareChose,each number is: %d %d %d %d\n",y1,y2,x1,x2);
    for(int i = y2;i <= y1;i++)
    {
        for(int j = x1;j <= x2;j++)
        {
            enableLayer[i][j] = 1;
        }
    }
printf("leave squareChose\n");
}

void Inverse(BMP_FILE *bmp)//反向选择，不知道这个函数名对不对
{
    int **enableLayer = bmp->enableLayer;
    for(int i = 0;i < (bmp->picInfo).biHeight;i++)
    {
        for(int j = 0;j < (bmp->picInfo).biWidth;j++)
        {
            enableLayer[i][j] = enableLayer[i][j] ^ 1;
        }
    }
}
//复制一个图片之前要free之前复制的图片
BMP_FILE* copyImage(BMP_FILE *bmp)//复制bmp中被选中的部分，存入copy中
{
printf("In to copy\n");
    BMP_COLOR color = {0,0,0};
    int height = bmp->picInfo.biHeight;
    int width = bmp->picInfo.biWidth;
    BMP_COLOR** image = createImage(height,width,color);
    int** enable = createEnableLayer(height,width);
    printf("create function all fine\n");
    for(int i = 0;i < height;i++)
    {
        for(int j = 0;j < width;j++)
        {
            image[i][j] = (bmp->data.image)[i][j];
            enable[i][j] = (bmp->enableLayer)[i][j];
        }
    }
    printf("loop works fine\n");
    BMP_FILE* copy = (BMP_FILE*)malloc(sizeof(BMP_FILE));
    copy->picInfo.biHeight = height;
    copy->picInfo.biWidth = width;
    copy->data.image = image;
    copy->enableLayer = enable;
    printf("leave copy\n");
    return copy;
}

void pasteImage(BMP_FILE* bmp,BMP_FILE* copy,int y,int x)//FIXME:
{
    changeY(bmp,&y);
    printf("Y is:%d\n",y);
    printf("In to paste\n");
    //int height = bmp->picInfo.biHeight;
    int width = bmp->picInfo.biWidth;
    int sHeight = copy->picInfo.biHeight;
    int sWidth = copy->picInfo.biWidth;
    for(int i = y;i > 0 && i - y < sHeight;i--)
    {
        for(int j = x;j < width && j - x < sWidth;j++)
        {
            //("IN LOOP\n");
            printf("PP: %d %d\n",i,j);
            printf("%d %d\n",sHeight - i + y - 1,j - x);
            if((copy->enableLayer)[sHeight - i + y - 1][j - x] == 1)
            {
                printf("IN PASTE\n");
                ((bmp->data).image)[i][j] = ((copy->data).image)[sHeight - i + y][j - x];
            }
        }
    }
    
    int flag = 0;
    for(int i = 0;i < sHeight;i++)
    {
        for(int j = 0;j < sWidth;j++)
        {
            if((copy->enableLayer)[i][j] == 1) flag += 1;
        }
    }
    if(flag)printf("YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS %d\n",flag);

    printf("leave paste\n");
}

void drawLine(BMP_FILE *bmp,int x1,int y1,int x2,int y2)
{
    changeYs(bmp,&y1,&y2);
}

void drawCircle(BMP_FILE *bmp,int x,int y,int r)
{
    changeY(bmp,y);
}