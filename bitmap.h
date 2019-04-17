#ifndef BITMAP_H
#define BITMAP_H
#include<QVector>
#include<stdio.h>
#include<windows.h>
#define BITMAP_ID 0x4D42
#include "reference.h"

class bitmap_load
{
public:
   bitmap_load();
    ~bitmap_load();

    bool LoadBitmap(const char *filename); //加载位图
    void FreeImage();                      //释放图像数据
    bool Load(const char* fileName);       // 载入位图并创建纹理

    unsigned int ID;                 // 生成纹理的ID号
    int imageWidth;                // 图像宽度
    int imageHeight;                // 图像高度
    unsigned char *image;            //指向图像数据的指针

};

#endif // BITMAP_H
