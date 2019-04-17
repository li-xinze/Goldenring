#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>
#define MAP 40

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QPixmap pix(":/login/pic/mainlogo.png");
    QSplashScreen splash(pix);
    splash.resize(pix.size());
    splash.show();

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
