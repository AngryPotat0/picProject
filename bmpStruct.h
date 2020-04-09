#ifndef BMP_STRUCT
#define BMP_STRUCT

typedef unsigned char BYTE; //1 byte
typedef unsigned short DWORD; //2 bytes
typedef unsigned int DATA; //4 bytes

typedef struct{
    DWORD bfType;//bmp 文件标识 BM
    DATA bfSize;//length of whole bmp file
    DATA bfResv;//useless
    DATA bfOffBits;//偏移数，即 位图文件头+位图信息头+调色板 的大小
}BMP_HEADER;//固定14

typedef struct{
    DATA biSize;//位图信息头的大小，固定40
    DATA biWidth;//位图的宽度，像素
    DATA biHeight;
    DWORD biPlanes;//固定值1
    DWORD biBitCount;//每个像素的位数1-黑白图，4-16色，8-256色，24-真彩色
    DATA biCompression;//压缩方式，0表示不压缩，1表示RLE8压缩，2表示RLE4压缩，3表示每个像素值由指定的掩码决定
    DATA biSizeImage;//位图全部像素占用的字节数，BI_RGB时可设为0 也可以不为零
    DATA biXPelsPerMeter;//水平分辨率(像素/米)  当0处理就行。。。。下面那个一样
    DATA biYPelsPerMeter;//垂直分辨率(像素/米)
    DATA biClrUsed;//位图使用的颜色数如果为0，则颜色数为2的biBitCount次方
    DATA biClrImportant;//重要的颜色数，0代表所有颜色都重要
}BMP_INFOHEAD;
//biSize，biPlanes，biBitCount这几个数值是固定的。想偷懒的话，其它的数值可以一律用0来填充。
//24位真彩色位图没有颜色表
typedef struct{
    BYTE blue;
    BYTE green;
    BYTE red;
    //int flag;//复制粘贴之类的用。。。。挺蠢的，一般用不到这玩意儿
    //经过慎重考虑之后，我还是放弃了上面这个愚蠢的设计，转而使用一种更加愚蠢的设计
}BMP_COLOR;

typedef struct
{
    int skip;
    BMP_COLOR **image;//图像数据指针
}BMP_DATA;

typedef struct
{
    BMP_HEADER head;
    BMP_INFOHEAD picInfo;
    BMP_DATA data;
    int** enableLayer;
}BMP_FILE;//bmp文件结构，所有信息存于此结构内


#endif