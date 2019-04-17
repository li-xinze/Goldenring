#ifndef SKY_H
#define SKY_H
#include "ob.h"
#include"bitmap.h"


#define GL_CLAMP_TO_EDGE    0x812F

class Sky
{
public:


    Sky();
    ~Sky();
    bool Init();
    void  CreateSky(float x, float y, float z,
                       float width, float height,
                       float length);

private:
    bitmap_load bit_map[6];

};

#endif // SKY_H
