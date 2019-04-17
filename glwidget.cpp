#include "glwidget.h"
#include <QImage>
#include<windows.h>
#include<math.h>
#include <QKeyEvent>
#include <QDesktopWidget>
#include<QApplication>
#include<QGraphicsOpacityEffect>
#include<qstandardpaths.h>
#include<QTimer>


glWidget::glWidget(QWidget* parent):QGLWidget(parent)
{
    hitcount=0;
    moster_alive = true;
    newplayer = false;
    self_Moved = 1.0;
    status_reciever =new Status_Reciver;
    send_status = new Send_Status;
    sky = new Sky;
    condition = true;
    g_eye[0]= -100.0;
    g_eye[2]= 40.0;
      g_Angle=0;
      g_elev=0;
      g_eye[1] = 6.0;
      g_look[0] = 0.0;
      g_look[1] = 0.0;
      g_look[2] = 0.0;
    scale = 1.0;
    wid =QApplication::desktop()->width();
    hei =QApplication::desktop()->height();
    QCursor cursor;
    //cursor.setShape(Qt::SizeAllCursor);
    setCursor(cursor);
    QPoint center = mapToGlobal(QPoint(wid/2,hei/2));
    QCursor::setPos(center);
    setCursor(Qt::BlankCursor);
    QFont font;
    font.setPointSize(12);
    MDL = new DynamicMDL();
    ball = new ObjLoader();
    house=new ObjLoader();
    SaveKeyReleased(Key_A);
    SaveKeyReleased(Key_D);
    SaveKeyReleased(Key_W);
    SaveKeyReleased(Key_S);
    timer2 = new QTimer(this);

    timer1 = new QTimer(this);
    timer1->start(1000);
    connect(timer1,SIGNAL(timeout()),this,SLOT(back()));
    timer2->start(16);
    connect(timer2,SIGNAL(timeout()),this,SLOT(rerender()));
    timer2->start(16);
    connect(timer2,SIGNAL(timeout()),this,SLOT(DisplayScene()));
    this->setFocus();
}
void glWidget::back(){
    MDL->afterhit();
}

void glWidget::mouseMoveEvent(QMouseEvent *event)
{

    QPoint p ,pos;
    p = event->globalPos();
    pos = p-QPoint(wid/2,hei/2);
    g_Angle += pos.x()*0.02f;
    g_elev  -= pos.y()*0.02f;
    QCursor::setPos(QPoint(wid/2,hei/2));
    rad_xz = float (3.13149*g_Angle/180.0f);
    //g_eye[1] =40.0;
    g_look[0] = float(g_eye[0] + 100*cos(rad_xz));
    g_look[2] = float(g_eye[2] + 100*sin(rad_xz));
    //g_look[1] = g_eye[1];
}
bool glWidget::fcl(){
    Vector3f v1(-47.1,0.0,70.67);
    Vector3f v2(-4.5,8.0,90.67);
    Vector3f v3(47.1,0.0,70.67);
    Vector3f v4(4.5,8.0,90.67);
    Vector3f v5(-37.1,0,90.67);
    Vector3f v6(-57.1,8,-20.67);
    Vector3f v7(37.1,0,90.67);
    Vector3f v8(47.1,8,-20.67);
    Vector3f v9(-35.1,0,-5.67);
    Vector3f v10(-70.1,8,-15.67);
    Vector3f c1(-48.1837,12,45.5586);
    Vector3f c2(-90.1,16,42.567);
    Vector3f eye(g_eye[0],g_eye[1],g_eye[2]);
    const  AABBf wall_l(v1,v2);
    const  AABBf wall_r(v3,v4);
    const  AABBf wallc_l(v5,v6);
    const  AABBf wallc_r(v7,v8);
    const  AABBf walls_L(v9,v10);
    const  AABBf chair1(c1,c2);

   // const  AABBf walls_R(v11,v12);
    //const  AABBf wallc_r(v7,v8);
    AABBf man(eye);

    //model1->beginModel();
    //model1->addSubModel(vertices1);
    //model1->endModel();
    /*Matrix3f R1;
    Vector3f T1;
    R1 << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    T1[0]=0.0;T1[1]=0.5;T1[2]=0.0;
    //CollisionObject* obj1= new CollisionObjectf(model1,Transform3f(R1,T1););
   // Model* model2 = new Model();
    //model2->beginModel();
    //model2->addVertex(eye);
    //model2->endModel();
    Matrix3f R2;
    Vector3f T2;
    R2 << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    T2[0]=0.0;T2[1]=0.0;T2[2]=0.0;
    //CollisionGeometryf
    //std::shared_ptr<AABB>
    //CollisionObjectf* obj2= new CollisionObjectf(model2,Transform3f(R2,T2););
    CollisionRequestf request;
    CollisionResultf result;
    //collide(obj1,obj2,request,result);
    Transform3f tf1,tf2;
    tf1.setIdentity();
    tf2.setIdentity();
    collide()
    collide(a1,tf1,a2,tf2,request,result);*/
    if(man.overlap(wall_l)||man.overlap(wall_r)||man.overlap(wallc_l)||man.overlap(wallc_r)
            ||man.overlap(walls_L)){
        return true;
    }
    else{
        return false;
    }

        if(man.overlap(chair1)){
            return true;
        }
        else{
            return false;
        }

}
void glWidget::initLight()
{
    //set lights
    GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
    GLfloat mat_shiniess[] = {100.0};
    GLfloat light_ambient [4] = {1.0,1.0,1.0,1.0};
    GLfloat light_diffuse [4] = {1.0,1.0,1.0,1.0};
    GLfloat light_specular[4] = {1.0,1.0,1.0,1.0};
    GLfloat light_position[4] = {1500.0,1500.0,1500.0,0.0};

    GLfloat lmodel_ambient [] = {1.0,1.0,1.0,1.0};

    //create light
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shiniess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);   //
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);//
    glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}
void glWidget::initializeGL()
{
    glewInit();
    char desktopPath[100];
    int i;
    for(i=0; i<QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).size();i++)
    {
        desktopPath[i] = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)[i].toLatin1();
    }
    desktopPath[i] = '\0';
    //setGeometry(0.0,0.0,1000,680);
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    initLight();
    MDL->init(1);
    MDL->init(2);
    //tex
    //glEnable(GL_TEXTURE_2D);
    //char path[100];
    if (sky->Init())
        {
            qDebug()<<"sky created -----------------------------------";
        }

}
void glWidget::resizeGL(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble rFov = 40.0 * 3.14159265 / 180.0;
        glFrustum( -0.1 * tan( rFov / 2.0 ) * (GLdouble)w/(GLdouble)h,
                  0.1 * tan( rFov / 2.0 ) * (GLdouble)w/(GLdouble)h,
                  -0.1 * tan( rFov / 2.0 ),
                  0.1 * tan( rFov / 2.0 ),
                  0.1, 10000.0 );
}
void glWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(g_eye[0],g_eye[1],g_eye[2],
            g_look[0],g_look[1]+g_elev,g_look[2],     
            0.0,1.0,0.0);                           
    glColor3f(1.0,1.0,1.0);
   // glPushMatrix();
    glRotatef(0,1.0,0.0,0.0);
    glRotatef(0,0.0,1.0,0.0);
    glScalef(scale,scale,scale);
    MDL->render(1,0.0,0.0,0.0,0.0,1.0);
    if(moster_alive){
    MDL->render(2,0.0,0.0,0.0,0.0,1.0);
    }
    glPushMatrix();
    //glRotatef(-90.0,0.0,1.0f,0.0f);
    glTranslatef(20.0,0.5,150.0);
    glScalef(0.10,0.10,0.10);
    if(condition == true)
    {
    house->loadFromFile("C:/moxing/Coffee_Shop.obj","C:/moxing/Coffee_Shop.mtl");
    }
    house->renderObj();
    glPopMatrix();

    int player_number = status_reciever->identify_list.size();
    qDebug()<<"player_number"<<player_number;
    for(int i = 0; i<player_number; i++){

 qDebug()<<"surprise";
        if(!newplayer){
        MDL->init(3);
        newplayer = true;
        }
    status_reciever->set_player_status(status_reciever->identify_list[i],
                                      model,Eye_x,Eye_y,Eye_z,G_angle,Moved);
    MDL->render(3,*Eye_x,*Eye_y,*Eye_z,*G_angle,*Moved);
    }
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glScalef(0.03,0.03,0.03);
    if(condition == true)
    {
    ball->loadFromFile("C:/moxing/jiaotang.obj","C:/moxing/jiaotang.mtl");
    qDebug()<<"1";
    }
    ball->renderObj();
    glPopMatrix();

    condition = false;
    glPushMatrix();
    glTranslatef(-220.0,0.0,-120);
    sky->CreateSky(0, 0, 0, 200.0, 200.0, 200.0);
    glPopMatrix();
}
/*void glWidget::loadTexture(QString filepath, GLuint *texture)
{
    QImage tex, buf;

    if(!buf.load(filepath))
    {
        qDebug()<<"error:"<<filepath<<"failed to texture image!";
        exit(0);
    }
    glEnable(GL_TEXTURE_2D);
    tex = convertToGLFormat(buf);
    glGenTextures(1, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());//瀵偓婵婀″锝呭灡瀵よ櫣姹楅悶鍡樻殶閹
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}*/
void glWidget::keyPressEvent( QKeyEvent* event )
{
    switch ( event->key( ) )
    {
    case Qt::Key_W: {
        SaveKeyPressed( Key_W );
        self_Moved = 2.0;

        break;
    }
    case Qt::Key_S: {
        SaveKeyPressed( Key_S);
        self_Moved = 2.0;

        break;
        }
    case Qt::Key_A:{
        SaveKeyPressed( Key_A);
        self_Moved = 2.0;

        break;
        }
    case Qt::Key_D:{
            SaveKeyPressed( Key_D );
            self_Moved = 2.0;

            break;
    }
    case Qt::Key_Escape:{
        this->setWindowFlags(Qt::SubWindow);
        this->showNormal();
        delete this;
        break;
    }
    default: break;
    }

}
void glWidget::keyReleaseEvent( QKeyEvent* event )
{
    switch ( event->key( ) )
    {
    case Qt::Key_W:{
       if(!event->isAutoRepeat()){
        SaveKeyReleased( Key_W );
        self_Moved = 1.0;

       }
        break;
    }
    case Qt::Key_S:
        if(!event->isAutoRepeat()){
        SaveKeyReleased( Key_S );
        self_Moved = 1.0;

        }
        break;
    case Qt::Key_A:
        if(!event->isAutoRepeat()){
        SaveKeyReleased( Key_A );
        self_Moved = 1.0;

        }
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat()){
        SaveKeyReleased( Key_D );
        self_Moved = 1.0;

        }
        break;
    default: break;
    }
}
void glWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        if(scale+0.05 <= 1.2)
        {
        scale+=0.05;
        updateGL();
        }
    }
    else if(event->delta() < 0)
    {
        if(scale-0.05 >= 1.0)
        {
            scale-=0.05;
            updateGL();
        }
    }
}
void glWidget::DisplayScene()
{
    fcl();
    float x=g_eye[0],y=g_eye[1],z=g_eye[2];
    float speed = 0.4f;
    int i = 0;
    if (KeyPressed( Key_D ))  {
        g_Angle+=speed;
        i++;
    }
    if (KeyPressed( Key_A )) {
        g_Angle-=speed;
        i++;
    }
    rad_xz = float (3.13149* g_Angle/180.0f);
    //if (event->key() == Qt::Key_Up) glArea->g_elev +=2.0f;
    //if (event->key() == Qt::Key_Down) glArea->g_elev -=2.0f;
    if (g_elev<-30)	g_elev  =-30;
    if (g_elev>30)	g_elev  = 30;
    if (KeyPressed( Key_W ))
    { g_eye[2]+=sin(rad_xz)*speed;
      g_eye[0]+=cos(rad_xz)*speed;
      i++;
    }
    if (KeyPressed( Key_S ))
    { g_eye[2]-=sin(rad_xz)*speed;
      g_eye[0]-=cos(rad_xz)*speed;
      i++;
    }
    //if (glArea->g_eye[0]<-(MAP*2-20))	glArea->g_eye[0]= -(MAP*2-20);
    //if (glArea->g_eye[0]> (MAP*2-20))	glArea->g_eye[0]=  (MAP*2-20);
    //if (glArea->g_eye[2]<-(MAP*2-20))	glArea->g_eye[2]= -(MAP*2-20);
    //if (glArea->g_eye[2]> (MAP*2-20))	glArea->g_eye[2]=  (MAP*2-20);
    //g_eye[1] =6.0;
     qDebug()<<g_eye[0];
     qDebug()<<g_eye[2];
     //g_eye[0]=13;
    if((-47.1<g_eye[0])&&(g_eye[0]<-21.23)&&(35.67<g_eye[2])&&(g_eye[2]<55.55)&&(g_eye[1])){
    g_eye[1] =6.00+0.5*(-21.23-g_eye[0]);
    qDebug()<<g_eye[1];
    while(g_eye[1] > 13){
        g_eye[1]=13;
    }
    if(!(-90.1<g_eye[0])&&(g_eye[0]<-21.23)){
         g_eye[1]=6;
    }
    }




    fcl();
    zangan(x,z);
    g_look[0] = float(g_eye[0] + 100*cos(rad_xz));
    g_look[2] = float(g_eye[2] + 100*sin(rad_xz));
    g_look[1] = g_eye[1];
    if(KeyPressed( Key_A )||KeyPressed( Key_D )||KeyPressed( Key_W )||KeyPressed( Key_S )){
        MDL->change_model_press(1);
    }
    else{
         MDL->change_model_release(1);
    }
    //send self information
    //self_identify = status_reciever->get_self_identify();
    self_identify = "2";
    send_status->send(self_identify,g_eye[0],g_eye[1],g_eye[2],g_Angle,self_Moved);
}
int  glWidget::zangan(float x,float z)
{ float pp;
    if(fcl())
    {
     pp=g_eye[0];g_eye[0]=x;
     if(!fcl())  return 0;
     else g_eye[0]=pp;
     pp=g_eye[2];g_eye[2]=z;
     if(!fcl())  return 0;
     else g_eye[2]=pp;
     return 0;
    }
    return 0;
}
void glWidget::rerender(){

    this->update();
}
void glWidget::mousePressEvent(QMouseEvent *e)
{

    if (Qt ::LeftButton == e->button())
    {
        hitcount++;
        if(hitcount<8){
             qDebug()<<"hit";
            MDL->MOUSEPRESS();
        }
        else{
            moster_alive = false;
        }
    }
}
