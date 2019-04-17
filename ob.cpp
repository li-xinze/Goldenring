#include "ob.h"

ObjLoader::ObjLoader()
{

}

void ObjLoader::loadFromFile(QString objfile,QString mtlfile)
{
    loadMtlFile(mtlfile);
    loadObjFile(objfile);
    transToVAO();
}
void ObjLoader::loadMtlFile(QString filename)
{
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Error: Mtl File cannot be opened!";
        exit(-2);
    }
    QTextStream ts(&f);

    int index = -1; // 当前材质的下标

    while(!ts.atEnd())
    {
        QString line = ts.readLine();

        QStringList strList = line.split(QRegExp("(\\s+)"));  // 去除空白字符
        strList.removeAll("");

        if(strList.size() <= 0)
            continue;

        // 正式读取mtl
        if(strList[0] == "newmtl")
        {
            Material* tMtl = new Material();

            tMtl->mtlName = strList[1];
            m_mtls.push_back(tMtl);  // 获得一个新的材质 //m_mtls

            index = m_mtls.size()-1;
        }
        if(strList[0] == "Ns")
        {
            m_mtls[index]->Ns = strList[1].toDouble();
        }
        if(strList[0] == "Ka")
        {
            m_mtls[index]->Ka[0] = strList[1].toDouble();
            m_mtls[index]->Ka[1] = strList[2].toDouble();
            m_mtls[index]->Ka[2] = strList[3].toDouble();
        }
        if(strList[0] == "Kd")
        {
            m_mtls[index]->Kd[0] = strList[1].toDouble();
            m_mtls[index]->Kd[1] = strList[2].toDouble();
            m_mtls[index]->Ks[2] = strList[3].toDouble();
        }
        if(strList[0] == "Ks")
        {
            m_mtls[index]->Ks[0] = strList[1].toDouble();
            m_mtls[index]->Ks[1] = strList[2].toDouble();
            m_mtls[index]->Ks[2] = strList[3].toDouble();
        }
        if(strList[0] == "map_Kd")
        {
            QString imgPath = "C:/wenli/"+strList[1];
            qDebug()<<strList[1];
            if(!FileAccessor::exist(imgPath))  // 看看纹理是否存在
                continue;
            else
            m_mtls[index]->hasTexture = true;
            qDebug()<<"read the materia..............................................";

            Texture::loadTexture(imgPath,&m_mtls[index]->texture);
        }
    }
}

void ObjLoader::loadObjFile(QString filename)
{
    QFile f(filename);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Error: Mtl File cannot be opened!";
        exit(-2);
    }

    QTextStream ts(&f);

    int id = -1;   // 当前正在添加面的材质Id

    while(!ts.atEnd())
    {
        QString line = ts.readLine();

        QStringList strList = line.split(QRegExp("(\\s+)|/"));  // 去除空白字符
        strList.removeAll("");

        if(strList.size() <= 0)
            continue;

        // 正式开始读取


        if(strList[0] == "v")
        {
            Point3 tmp(strList[1].toDouble(),strList[2].toDouble(),strList[3].toDouble());
            vertexs.push_back(tmp);
        }
        if(strList[0] == "vt")
        {
            Point3 tmp(strList[1].toDouble(),strList[2].toDouble(),0.00000);
            textures.push_back(tmp);
        }
        if(strList[0] == "vn")
        {
            Point3 tmp(strList[1].toDouble(),strList[2].toDouble(),strList[3].toDouble());
            normals.push_back(tmp);
        }

        if(strList[0] == "usemtl")
        {
            for(int i=0; i < m_mtls.size(); i++)  // 找到对应名称的材质
            {
                if( strList[1] == m_mtls[i]->mtlName)
                {
                    id = i;
                    break;
                }
            }
        }
        if(strList[0] == "f")
        {
            for(int i=0; i<strList.size()-1;i++)
            {
                if(strList.size() == 13)
                    m_mtls[id]->quadFaces.push_back(strList[i+1].toInt());
                if(strList.size() == 10)
                    m_mtls[id]->triFaces.push_back(strList[i+1].toInt());
            }
        }
    }
}

void ObjLoader::transToVAO()
{
    int sum = 0;
    for(int i=0; i<m_mtls.size();i++)
    {
        // 四角面和三角面的个数:
        m_mtls[i]->quadNum = m_mtls[i]->quadFaces.size()/12;
        m_mtls[i]->triNum = m_mtls[i]->triFaces.size()/9;

        m_mtls[i]->triVertexs = new GLdouble[m_mtls[i]->triNum*3*3];
        m_mtls[i]->triTextures = new GLdouble[m_mtls[i]->triNum*3*3];
        m_mtls[i]->triNormals = new GLdouble[m_mtls[i]->triNum*3*3];

        m_mtls[i]->quadVertexs = new GLdouble[m_mtls[i]->quadNum*4*3];
        m_mtls[i]->quadTextures = new GLdouble[m_mtls[i]->quadNum*4*3];
        m_mtls[i]->quadNormals = new GLdouble[m_mtls[i]->quadNum*4*3];

        sum+=(m_mtls[i]->triNum+m_mtls[i]->quadNum);

        for(int j=0; j<m_mtls[i]->triNum ; j++)  // 第几个三角面
        {
            //qDebug()<<"三角面"<<j;
            for(int k=0; k<3;k++) // 第j个三角面的第k个点
            {
                m_mtls[i]->triVertexs[j*3*3+k*3+0] = vertexs[m_mtls[i]->triFaces[j*9+k*3+0]-1].x;
                m_mtls[i]->triVertexs[j*3*3+k*3+1] = vertexs[m_mtls[i]->triFaces[j*9+k*3+0]-1].y;
                m_mtls[i]->triVertexs[j*3*3+k*3+2] = vertexs[m_mtls[i]->triFaces[j*9+k*3+0]-1].z;

                m_mtls[i]->triTextures[j*3*3+k*3+0] = textures[m_mtls[i]->triFaces[j*9+k*3+1]-1].x;
                m_mtls[i]->triTextures[j*3*3+k*3+1] = textures[m_mtls[i]->triFaces[j*9+k*3+1]-1].y;
                m_mtls[i]->triTextures[j*3*3+k*3+2] = textures[m_mtls[i]->triFaces[j*9+k*3+1]-1].z;

                m_mtls[i]->triNormals[j*3*3+k*3+0] = normals[m_mtls[i]->triFaces[j*9+k*3+2]-1].x;
                m_mtls[i]->triNormals[j*3*3+k*3+1] = normals[m_mtls[i]->triFaces[j*9+k*3+2]-1].y;
                m_mtls[i]->triNormals[j*3*3+k*3+2] = normals[m_mtls[i]->triFaces[j*9+k*3+2]-1].z;
            }
        }

        for(int j=0; j<m_mtls[i]->quadNum ; j++)  // 第几个四角面
        {
            for(int k=0; k<4 ;k++) // 第j个三角面的第k个点
            {
                m_mtls[i]->quadVertexs[j*4*3+k*3+0] = vertexs[m_mtls[i]->quadFaces[j*12+k*3+0]-1].x;
                m_mtls[i]->quadVertexs[j*4*3+k*3+1] = vertexs[m_mtls[i]->quadFaces[j*12+k*3+0]-1].y;
                m_mtls[i]->quadVertexs[j*4*3+k*3+2] = vertexs[m_mtls[i]->quadFaces[j*12+k*3+0]-1].z;

                m_mtls[i]->quadTextures[j*4*3+k*3+0] = textures[m_mtls[i]->quadFaces[j*12+k*3+1]-1].x;
                m_mtls[i]->quadTextures[j*4*3+k*3+1] = textures[m_mtls[i]->quadFaces[j*12+k*3+1]-1].y;
                m_mtls[i]->quadTextures[j*4*3+k*3+2] = textures[m_mtls[i]->quadFaces[j*9+k*3+1]-1].z;


                m_mtls[i]->quadNormals[j*4*3+k*3+0] = normals[m_mtls[i]->quadFaces[j*12+k*3+2]-1].x;
                m_mtls[i]->quadNormals[j*4*3+k*3+1] = normals[m_mtls[i]->quadFaces[j*12+k*3+2]-1].y;
                m_mtls[i]->quadNormals[j*4*3+k*3+2] = normals[m_mtls[i]->quadFaces[j*12+k*3+2]-1].z;

            }
        }
    }
    qDebug()<<"trasfom to render";
}

void ObjLoader::renderObj()
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    for(int i=0; i<m_mtls.size();i++)

    {
        if(m_mtls[i]->hasTexture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,m_mtls[i]->texture);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            //glColor3f(1.0f,1.0f,1.0f);
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            //glColor3fv(m_mtls[i]->Kd);
        }

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_mtls[i]->Ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_mtls[i]->Kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_mtls[i]->Ks);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_mtls[i]->Ns);



        glVertexPointer(3,GL_DOUBLE,0,m_mtls[i]->triVertexs);
        glNormalPointer(GL_DOUBLE,0,m_mtls[i]->triNormals);
        glTexCoordPointer(3,GL_DOUBLE,0,m_mtls[i]->triTextures);

        glDrawArrays(GL_TRIANGLES,0,m_mtls[i]->triNum*3);

        glVertexPointer(3,GL_DOUBLE,0,m_mtls[i]->quadVertexs);
        glNormalPointer(GL_DOUBLE,0,m_mtls[i]->quadNormals);
        glTexCoordPointer(3,GL_DOUBLE,0,m_mtls[i]->quadTextures);
        glDrawArrays(GL_QUADS,0,m_mtls[i]->quadNum*4);

    }
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}
