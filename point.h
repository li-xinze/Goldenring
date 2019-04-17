/*#ifndef POINT_H
#define POINT_H
#include <QGLWidget>
#include <QVector>
#include <vector>
#include <QtGui>
#include <QtCore>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glaux.h>

class point3
{
public:
    float x;
    float y;
    float z;
};

class group1     //使用纹理____一行format
{
public:
    int style;
    GLfloat colorv[3];
    QVector<unsigned int> vIndix;

    group1(){}
    group1(int* ptr, int count)
    {
        for(int i=0; i< count ; i++)
        {
            vIndix.push_back(ptr[i]);
        }
    }
};

class group     //不适用纹理____一行format
{
public:
    int style;
    GLfloat colorv[3];
    QVector<unsigned int> vIndix;   //存放一行f

    group(){}
    group(int* ptr, int count,char* pCurrent)
    {
        for(int i=0; i< count ; i++)
        {
            vIndix.push_back(ptr[i]);
        }

        toID(pCurrent);
        toColorv();
    }

    void toID(char* type)   //mtl
    {
        if(strcmp(type,"Door")==0)
            style = 0;
        else if(strcmp(type,"Fence") ==0)
            style = 1;
        else if(strcmp(type,"Foothpath")==0)
            style = 2;
        else if(strcmp(type,"Grass")==0)
            style = 3;
        else if(strcmp(type,"Landscape")==0)
            style = 4;
        else if(strcmp(type,"Leaf")==0)
            style = 5;
        else if(strcmp(type,"Road")==0)
            style = 6;
        else if(strcmp(type,"Rock")==0)
            style = 7;
        else if(strcmp(type,"Roof")==0)
            style = 8;
        else if(strcmp(type,"Roof.001")==0)
            style = 9;
        else if(strcmp(type,"Roof.002")==0)
            style = 10;
        else if(strcmp(type,"Topper") ==0)
            style = 11;
        else if(strcmp(type,"Tree") ==0)
            style = 12;
        else if(strcmp(type,"Window") ==0)
            style = 13;
        else if(strcmp(type,"Window_aligment") ==0)
            style = 14;
        else if(strcmp(type,"Window_aligment.001") ==0)
            style = 15;
        else if(strcmp(type,"house") ==0)
            style = 16;
        else if(strcmp(type,"house.001") ==0)
            style = 17;
        else if(strcmp(type,"house.002") ==0)
            style = 18;
        else if(strcmp(type,"water") ==0)
            style = 18;
        else
            style = -1;
    }

    void toColorv()
    {
        if(style == 0)
        {
            colorv[0] =0.161521;colorv[1]=0.043425;colorv[2]= 0.009558;
        }
        else if(style == 1)
        {
            colorv[0] =0.115263;colorv[1]=0.501330;colorv[2]= 0.295700;
        }
        else if(style == 2)
        {
            colorv[0] =0.301010;colorv[1]=0.216398;colorv[2]= 0.203322;
        }
        else if(style == 3)
        {
            colorv[0] =0.065826;colorv[1]=0.190718;colorv[2]= 0.005999;
        }
        else if(style == 4)
        {
            colorv[0] =0.548387;colorv[1]=0.639282;colorv[2]= 0.110764;
        }
        else if(style == 5)
        {
            colorv[0] =0.137988;colorv[1]=0.366025;colorv[2]= 0.025955;
        }
        else if(style == 6)
        {
            colorv[0] =0.024851;colorv[1]=0.024851;colorv[2]= 0.024851;
        }
        else if(style == 7)
        {
            colorv[0] =0.182467;colorv[1]=0.158671;colorv[2]= 0.186413;
        }
        else if(style == 8)
        {
            colorv[0] =0.590328;colorv[1]=0.277363;colorv[2]= 0.042289;
        }
        else if(style == 9)
        {
            colorv[0] =0.590328;colorv[1]=0.046549;colorv[2]= 0.042785;
        }
        else if(style == 10)
        {
            colorv[0] =0.104233;colorv[1]=0.590328;colorv[2]= 0.183208;
        }
        else if(style == 11)
        {
            colorv[0] =0.695109;colorv[1]=0.045017;colorv[2]= 0.049190;
        }
        else if(style == 12)
        {
            colorv[0] =0.213409;colorv[1]=0.086534;colorv[2]= 0.030858;
        }
        else if(style == 13)
        {
            colorv[0] =0.078738;colorv[1]=0.453989;colorv[2]= 0.640000;
        }
        else if(style == 14)
        {
            colorv[0] =0.326986;colorv[1]=0.640000;colorv[2]= 0.346350;
        }
        else if(style == 15)
        {
            colorv[0] =0.271409;colorv[1]=0.201866;colorv[2]= 0.640000;
        }
        else if(style == 16)
        {
            colorv[0] =0.040739;colorv[1]=0.321575;colorv[2]= 0.066057;
        }
        else if(style == 17)
        {
            colorv[0] =0.609018;colorv[1]=0.220193;colorv[2]= 0.113065;
        }
        else if(style == 18)
        {
            colorv[0] =0.578434;colorv[1]=0.528341;colorv[2]= 0.179251;
        }
        else if(style == 19)
        {
            colorv[0] =0.094419;colorv[1]=0.426665;colorv[2]= 0.439081;
        }

    }
};


#endif // POINT_H*/
