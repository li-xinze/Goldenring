#include "objloader.h"

objloader::objloader()
{

    texture = new GLuint();

}

int objloader::multi(int num)  //计算10的num次幂(整数版)
{
    int res = 1;

    for(int i=0; i < num ; i++)
        res*=10;
    return res;
}

int objloader::toInt(char* str)  //将字符串转换为整型int
{
    int num;
    int temp=0;
    for(num=0 ; str[num]!= '\0';num++);
    int j;
    for(int i= num-1,j=0; i>=0; i--,j++)
    {
        temp+=(str[i]-48)*multi(j);

    }
    return temp;
}

int objloader::departLine(char *str, int *ptr)
{
    int startPos = 0;
    int count = 0;
    for(int i=0; true ;i++)
    {
        if( str[i] == '/' || str[i] == '\0' || str[i] ==' ' || str[i] =='\n')
        {
            char temp[15];
            int k,j;
            for(k=0, j= startPos; j < i ; j++,k++)
            {
                temp[k] = str[j];
            }
            temp[k] = '\0';
            ptr[count] = toInt(temp);
            count++;
            startPos += k+1;

            if(str[i] == '\0' || str[i] == '\n')
            {
                count--;
                for(int i = 0 ; i < count ; i++)
                {
                    ptr[i] = ptr[i+1];
                }
                return count;
            }
        }
    }
}

void objloader::loading(char * filepath)
{
    FILE* fp = fopen(filepath,"r");

    if(fp == NULL)
    {
        qDebug()<<"Impossible to open file!"<<"\n";
        return;
    }

    while(1)
    {
        char lineHeader[128];
        int res = fscanf(fp, "%s", lineHeader);

        if(res == EOF)
        {
            break;
        }

        if(strcmp(lineHeader,"v") == 0)
        {
            point3 vertex;
            fscanf(fp,"%f %f %f\n",&vertex.x,&vertex.y,&vertex.z);
            vertexes.push_back(vertex);
        }
        if(strcmp(lineHeader,"vn") == 0)
        {
            point3 vertex;
            fscanf(fp,"%f %f %f\n",&vertex.x,&vertex.y,&vertex.z);
            vNormals.push_back(vertex);
        }
        if(strcmp(lineHeader,"vt") == 0)
        {
            point3 vertex;
            fscanf(fp,"%f %f\n",&vertex.x,&vertex.y);
            vTexture.push_back(vertex);
        }

        else if(strcmp(lineHeader,"f") == 0)
        {
            int ptr[12];

            char temp[128];

            fgets(temp,128,fp);
            int count = departLine(temp,ptr);

            group1 element(ptr,count);

            indices.push_back(element);
        }
    }

    qDebug()<<"process: load the obj data";
}

void objloader::displayObj()
{
    for(int i=0; i<indices.size(); i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,*texture);
        glBegin(GL_POLYGON);
        for(int k=0; k<indices[i].vIndix.size();k+=3)
        {
            if(k+2 >= indices[i].vIndix.size())
                break;
            glNormal3f(vNormals[indices[i].vIndix[k+2]-1].x,vNormals[indices[i].vIndix[k+2]-1].y,vNormals[indices[i].vIndix[k+2]-1].z);
            glTexCoord2f(vTexture[indices[i].vIndix[k+1]-1].x,vTexture[indices[i].vIndix[k+1]-1].y);
            glVertex3f(vertexes[indices[i].vIndix[k]-1].x  ,vertexes[indices[i].vIndix[k]-1].y  ,vertexes[indices[i].vIndix[k]-1].z  );
        }
        glEnd();
    }
}
