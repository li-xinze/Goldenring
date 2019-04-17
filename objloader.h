#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <point.h>

class objloader
{
public:
    objloader();
    QVector<point3> vertexes;
    QVector<point3> vNormals;
    QVector<point3> vTexture;

    QVector<group1> indices;
    GLuint* texture;
    void loading(char* filepath);
    void displayObj();

protected:
    int multi(int num);
    int toInt(char* str);
    int departLine(char* str, int* ptr);

};

#endif // OBJLOADER_H
