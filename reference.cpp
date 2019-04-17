#include "reference.h"
Texture::Texture(){
    condition = true ;
}
 void Texture:: loadTexture(QString filepath, GLuint *texture)
{   if (condition = true){
    QImage buf;
    if(!buf.load(filepath))
    {
        printf("Error: failed to load image!");
        exit(1);
    }
    qDebug()<<"pictrue is loading ";

    tex = convertToGLFormat(buf);
    }
     qDebug()<<"pictrue is loadingjjjjjjjjjjjjj ";
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex.width(), tex.height(), GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    qDebug()<<tr("pictrue is loadedpppppppppppppppppppppppppppppppp");

}
