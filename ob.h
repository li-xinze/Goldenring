#ifndef OB_H
#define OB_H
#include "reference.h"
#include <QFile>
#include <QTextStream>
#include <exception>

class Material  // 材质下面管理一系列面
{
public:
    QString mtlName;

    double Ns;
    float Ka[3];
    float Kd[3];
    float Ks[3];

    bool hasTexture;
    GLuint texture; // 材料对应的纹理

    QVector<int> triFaces;  // 三个一组组成面
    QVector<int> quadFaces; // 四个一组组成面

    // vertex array object;
    int quadNum;  // 四角面个数
    int triNum;   // 三角面个数

    GLdouble *triVertexs;
    GLdouble *triNormals;
    GLdouble *triTextures;

    GLdouble *quadVertexs;
    GLdouble *quadNormals;
    GLdouble *quadTextures;

    Material():hasTexture(false){}
};

class ObjLoader
{
public:
    ObjLoader();

    void loadFromFile(QString objfile,QString mtlfile);
    void renderObj();
    bool condition;

private:
    // 临时数据 可以后期释放
    QVector<Point3> vertexs;
    QVector<Point3> textures;
    QVector<Point3> normals;
    QVector<Material*> m_mtls;

    void loadObjFile(QString filename);
    void loadMtlFile(QString filename);
    void transToVAO();
};

#endif // OBJLOADER_H
