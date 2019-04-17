#ifndef REFERENCE_H
#define REFERENCE_H
#define GLEW_STATIC
#include<GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <gl/gl.h>
#include <gl/glu.h>
#include<glut.h>
#include <QDebug>
#include <QFileInfo>
#include <cmath>
#define PAI 3.1415926
class Point2
{

    double x,y;
    Point2():x(0),y(0){}
    Point2(double x,double y):x(x),y(y){}
};

class Point3
{
public:
    double x,y,z;

    Point3():x(0),y(0),z(0){}

    Point3(double x,double y,double z):x(x),y(y),z(z){}
};



class Texture : public QGLWidget
{
public:
    Texture();
    static void loadTexture(QString filepath, GLuint *texture)
        {
            QImage buf,tex;
            if(!buf.load(filepath))
            {
                qDebug()<<filepath;
                printf("Error: failed to load image!");
                exit(1);
            }

            tex = convertToGLFormat(buf);


            glGenTextures(1, texture);
            glBindTexture(GL_TEXTURE_2D, *texture);
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex.width(), tex.height(), GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

        }
    };



class FileAccessor
{
public:

    static bool exist(QString filepath)
    {
        QFileInfo f(filepath);

        return f.exists();
    }

    static QString getFileName(QString filepath)
    {
        QStringList ls= filepath.split("/");

        return ls.at(ls.size()-1);
    }
};

class MyMath
{
public:
    static double mSin(double a){
        return sin(PAI*a/180.0);
    }

    static double mCos(double a){
        return cos(PAI*a/180.0);
    }
};

class Vec2{
public:
    double x;
    double y;

    Vec2():x(0),y(0){}
    Vec2(double x,double y):x(x),y(y){}
};

class Vec3{
public:
    double x,y,z;

    Vec3():x(0),y(0),z(0){}
    Vec3(double x,double y,double z):x(x),y(y),z(z){}

    Vec3 operator +(const Vec3& v)
    {
        Vec3 res;

        res.x = x+v.x;
        res.y = y+v.y;
        res.z = z+v.z;

        return res;
    }

    Vec3 operator -(const Vec3& v)
    {
        Vec3 res;

        res.x = x-v.x;
        res.y = y-v.y;
        res.z = z-v.z;

        return res;
    }
};

class Vector
{
public:
    static Point3 normalize(Point3& a, Point3& b, Point3& c)
    {


        Point3 normal, A, B;

        A = Point3(a.x-b.x,a.y-b.y,a.z-b.z);
        B = Point3(c.x-b.x,c.y-b.y,c.z-b.z);

        normal.x = A.y*B.z-A.z*B.y;
        normal.y = A.z*B.x-A.x*B.z;
        normal.z = A.x*B.y-A.y*B.x;

        return normal;
    }

    static Vec3 unit(const Vec3& v) //
    {
        double mod = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);

        return Vec3(v.x/mod,v.y/mod,v.z/mod);
    }

    static Vec3 multiple(const Vec3& v,const double& n)
    {
        return Vec3(v.x*n,v.y*n,v.z*n);
    }

    static Vec3 opposite(const Vec3& v)  //
    {
        return Vec3(-v.x,-v.y,-v.z);
    }

    static double getMod(const Vec3& v)
    {
        return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    }
};

#endif // REFERENCE_H
