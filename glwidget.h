#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "send_status.h"
#include"status_reciver.h"
#include "ob.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include<GL/glu.h>
#include<QLabel>
#include<sky.h>
#include<vector>
#include<fcl/math/bv/AABB.h>
#include<QLCDNumber>
#include<QDateTimeEdit>
#include<QDockWidget>
#include<QGridLayout>
#include"DynamicMDL.h"
#include"game_status.h"

using namespace fcl;
using namespace Eigen;

class glWidget : public QGLWidget
{
    Q_OBJECT
public:
    void glDrawString(unsigned char *str);
    //typedef BVHModel<OBBf> Model;
    // Model* model;
    bool fcl();
    ObjLoader* house;
    ObjLoader* ball;//'''''''''''''''''''''''''''''''''''';
    glWidget(QWidget *parent = 0);
    GLdouble	g_eye[3];
    GLdouble	g_look[3];
    float		rad_xz;
    float		g_Angle;
    float		g_elev;
    double scale;//
    double xPos,yPos,zPos;
    double yeye;
    //void loadTexture(QString filepath, GLuint* texture);
    bool condition;
protected:
    void initLight();                         //打光
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent( QKeyEvent* event );
    void keyReleaseEvent( QKeyEvent* event );
    void mousePressEvent(QMouseEvent *e);
private slots:
    void rerender();
    void DisplayScene();
    void back();

private:
    QWidget *shows;
    bool newplayer;
    QString self_identify;
    float *model;
    float *Eye_x ;
    float *Eye_y;
    float *Eye_z;
    float *G_angle;
    float *Moved;
    float self_Moved;
    DynamicMDL *MDL;

    bool mode;
     Status_Reciver *status_reciever;
     Send_Status *send_status;
    //QPoint p_lasttime;
    Sky *sky;
    int wid , hei;
    QTimer *timer2;
    QTimer *timer1;
    int hitcount;
    bool moster_alive;

    int zangan(float x,float z);                  //碰撞检测
    inline void SaveKeyPressed( int key )
    {
        m_PressedKeys |= ( 1 << key );
    }
    inline void SaveKeyReleased( int key )
    {
        m_PressedKeys &= ~( 1 << key );
    }
    inline bool KeyPressed( int key )
    {
        return m_PressedKeys & ( 1 << key );
    }
    enum Interested_Keys
    {
        Key_W = 1,
        Key_S,
        Key_A,
        Key_D
    };
    quint32 m_PressedKeys;


};


#endif // GLWIDGET_H
