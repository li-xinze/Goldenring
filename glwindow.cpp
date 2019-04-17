/*#include "glwindow.h"

#include <QDebug>

#include <QPainter>

#include <QDateTime>




void GLWindow::initializeGL()

{

    initializeOpenGLFunctions();

    QOpenGLFunctions *glFunc = this->context()->functions();

    glFunc->glClearColor(0.0f, 0.8f, 1.0f, 1.0f);





}



void GLWindow::resizeGL(int w, int h)

{

    mProjMatrix.setToIdentity();

    mProjMatrix.perspective(70.0f, GLfloat(w) / h, 0.001f, 10000.0f);

}





void GLWindow::paintGL()

{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    //    glEnable(GL_CULL_FACE);





}

*/









