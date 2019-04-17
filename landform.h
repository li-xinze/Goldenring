/*#ifndef LANDFORM_H
#define LANDFORM_H
#include "point.h"

class landform
{
public:
    landform();
    QVector<point3> vertexes;
    QVector<point3> vNormals;
    QVector<point3> vTexture;

    QVector<group> indices;

    char pCurrent[40];

    void loading(char* filepath);
    void showLandform();

protected:
    int multi(int num);
    int toInt(char* str);
    int departLine(char* str, int* ptr);

};

#endif // LANDFORM_H*/
