#include "bitmap.h"

    bitmap_load::bitmap_load()
    {
       /** 初始化成员值为0 */
        image = 0;
        imageWidth = 0;
        imageHeight = 0;
    }

    bitmap_load::~bitmap_load()
    {
       FreeImage();
    }

    bool bitmap_load::LoadBitmap(const char *file)
    {
        FILE *pFile = 0; /**< 文件指针 */

        /** 创建位图文件信息和位图文件头结构 */
        BITMAPINFOHEADER bitmapInfoHeader;
        BITMAPFILEHEADER header;

        unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

       /** 打开文件,并检查错误 */
        pFile = fopen(file, "rb");
            if(pFile == 0) qDebug()<<"flase have";

        /** 读入位图文件头信息 */
        fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

        /** 检查该文件是否为位图文件 */
        if(header.bfType != BITMAP_ID)
           {
               fclose(pFile);             /**< 若不是位图文件,则关闭文件并返回 */
               qDebug()<<"not bimap";
               return false;
           }

        /** 读入位图文件信息 */
        fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

        /** 保存图像的宽度和高度 */
        imageWidth = bitmapInfoHeader.biWidth;
        imageHeight = bitmapInfoHeader.biHeight;

        /** 确保读取数据的大小 */
       if(bitmapInfoHeader.biSizeImage == 0)
          bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
          bitmapInfoHeader.biHeight * 3;

        /** 将指针移到数据开始位置 */
        fseek(pFile, header.bfOffBits, SEEK_SET);

        /** 分配内存 */
        image = new unsigned char[bitmapInfoHeader.biSizeImage];

        /** 检查内存分配是否成功 */
        if(!image)                        /**< 若分配内存失败则返回 */
           {
               delete[] image;
               fclose(pFile);
               return false;
           }

        /** 读取图像数据 */
        fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

        /** 将图像颜色数据格式进行交换,由BGR转换为RGB */
        for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
           {
               textureColors = image[index];
               image[index] = image[index + 2];
               image[index + 2] = textureColors;
           }

        fclose(pFile);       /**< 关闭文件 */
        return true;         /**< 成功返回 */
    }

    // 载入位图文件，并创建纹理
    bool bitmap_load::Load(const char* fileName)
    {
        if(!LoadBitmap(fileName))
        {
            qDebug()<<"fail to load the bitmap";
            exit(0);
        }

        glGenTextures(1, &ID);


        glBindTexture(GL_TEXTURE_2D, ID);

        //控制滤波
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        // 创建纹理
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
                          imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
                          image);
       return true;
    }


    void bitmap_load::FreeImage()
    {

       if(image)
          {
             delete[] image;
             image = 0;
          }
    }


