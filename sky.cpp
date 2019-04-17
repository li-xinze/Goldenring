#include "sky.h"
#define MAP 40

Sky::Sky()
{
}

Sky::~Sky()
{
    for(int i =0 ;i< 6; i++)
    {
        bit_map[i].FreeImage();
        glDeleteTextures(1,&bit_map[i].ID);
    }
}
bool Sky::Init()
{
    char filename[128] ;
    char *bmpName[] = { "back","front","bottom","top","left","right"};
    for(int i=0; i< 6; i++)
    {
        sprintf(filename,"C:/sky/%s",bmpName[i]);
        strcat(filename,".bmp");
        qDebug()<<filename;

        if(!bit_map[i].LoadBitmap(filename))                    //载入位图文件
        {
           qDebug()<<"fall ";

        }
        glGenTextures(1, &bit_map[i].ID);                       //生成一个纹理对象名称

        glBindTexture(GL_TEXTURE_2D, bit_map[i].ID);            // 创建纹理对象

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bit_map[i].imageWidth,
                        bit_map[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
                        bit_map[i].image);
    }
    return true;

}


void  Sky::CreateSky(float x, float y, float z,
                            float box_width, float box_height,
                            float box_length)
{
    //获得场景中光照状态
    GLboolean lp;
    glGetBooleanv(GL_LIGHTING,&lp);

    //计算天空盒长 宽 高
    float width = MAP * box_width/8;
    float height = MAP * box_height/8;
    float length = MAP * box_length/8;

    //计算天空盒中心位置
    x = x+ MAP/8 - width  / 2;
    y = y+ MAP/24 - height / 2;
    z = z+ MAP/8 - length / 2;

    glDisable(GL_LIGHTING);            // 关闭光照


    glPushMatrix();
    glTranslatef(-x,-y,-z);


    glBindTexture(GL_TEXTURE_2D, bit_map[0].ID);

    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,          z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,         y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,         y,          z);

    glEnd();


    glBindTexture(GL_TEXTURE_2D, bit_map[1].ID);

    glBegin(GL_QUADS);


        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,         y,          z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,         y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,          z + length);

    glEnd();


    glBindTexture(GL_TEXTURE_2D, bit_map[2].ID);

    glBegin(GL_QUADS);


        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,         y,          z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,         y,          z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,          z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,          z);

    glEnd();


    glBindTexture(GL_TEXTURE_2D, bit_map[3].ID);

    glBegin(GL_QUADS);


        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,         y + height, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,         y + height, z);

    glEnd();


    glBindTexture(GL_TEXTURE_2D, bit_map[4].ID);

    glBegin(GL_QUADS);


        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,         y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,         y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,         y,          z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,         y,          z);

    glEnd();


    glBindTexture(GL_TEXTURE_2D, bit_map[5].ID);

    glBegin(GL_QUADS);


        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,          z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,          z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();

    glPopMatrix();

    if(lp)
        glEnable(GL_LIGHTING);

}
