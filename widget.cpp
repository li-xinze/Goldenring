#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QLabel>
//#include <testbutton.h>
#include <QGraphicsColorizeEffect>
#include<QElapsedTimer>
#include <QDesktopWidget>
#include<QApplication>
#include<QBitmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    int wid =QApplication::desktop()->width();
    int hei = wid * 2/3;
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(4000);
    timer2 = new QTimer(this);
    timer2->start(2);
    QGraphicsOpacityEffect *opacityEffect1=new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect2=new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect3=new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect4=new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect5=new QGraphicsOpacityEffect;
    opacityEffect1->setOpacity(0.3);
    opacityEffect2->setOpacity(0.3);
    opacityEffect3->setOpacity(0.3);
    opacityEffect4->setOpacity(0.3);
    opacityEffect5->setOpacity(0.3);
    ui->button1->setGraphicsEffect(opacityEffect1);
    ui->button2->setGraphicsEffect(opacityEffect2);
    ui->button3->setGraphicsEffect(opacityEffect3);
    ui->button4->setGraphicsEffect(opacityEffect4);
    ui->button5->setGraphicsEffect(opacityEffect5);
    ui->button1->setStyleSheet("color: white");
    ui->button2->setStyleSheet("color: white");
    ui->button3->setStyleSheet("color: white");
    ui->button4->setStyleSheet("color: white");
    ui->button5->setStyleSheet("color: white");

    stackWidget = new QAnimationStackedWidget(this);
    stackWidget->setGeometry(0,0,wid*7/30,hei*1/5);
    //QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
   // opacityEffect->setOpacity(0.0);
    //stackWidget->setGraphicsEffect(opacityEffect);

    QLabel* label1 = new QLabel(stackWidget);
    QLabel* label2 = new QLabel(stackWidget);
    QLabel* label3 = new QLabel(stackWidget);
    QLabel* label4 = new QLabel(stackWidget);
    QLabel* label5 = new QLabel(stackWidget);

    label1->resize(wid*7/30,hei*1/5);
    label2->resize(wid*7/30,hei*1/5);
    label3->resize(wid*7/30,hei*1/5);
    label4->resize(wid*7/30,hei*1/5);
    label5->resize(wid*7/30,hei*1/5);
    QPixmap pix1, pix2, pix3, pix4, pix5;
    pix1.load(":/login/pic/city1.jpg");

    QPixmap pic1 = pix1.scaled(label1->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label1->setPixmap(pic1);

    pix2.load(":/login/pic/city2.jpg");
    QPixmap pic2 = pix2.scaled(label2->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label2->setPixmap(pic2);

    pix3.load(":/login/pic/city3.jpg");
    QPixmap pic3 = pix3.scaled(label3->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label3->setPixmap(pic3);

    pix4.load(":/login/pic/city4.jpg");
    QPixmap pic4 = pix4.scaled(label4->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label4->setPixmap(pic4);

    pix5.load(":/login/pic/city5.jpg");
    QPixmap pic5 = pix5.scaled(label5->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label5->setPixmap(pic5);

    stackWidget->insertWidget(0, label1);
    stackWidget->insertWidget(1, label2);
    stackWidget->insertWidget(2, label3);
    stackWidget->insertWidget(3, label4);
    stackWidget->insertWidget(4, label5);
    connect(this->timer, SIGNAL(timeout()), stackWidget, SLOT(next()));
    connect(this->timer2, SIGNAL(timeout()), this, SLOT(changecolor()));
    //底层动态调控栏
    ui->widget_2->setGeometry(wid*1/10,hei*3/20,wid*3/25,hei*1/30);
    //ui->widget_2->setStyleSheet("background-color:black;");
    ui->widget_2->show();
    stackWidget->lower();
}
Widget::~Widget()
{
    if(stackWidget)
    {
        delete stackWidget;
        stackWidget = NULL;
    }
    delete ui;
}
void Widget::on_button1_clicked()
{   timer->stop();
    int index = stackWidget->currentIndex();
    qDebug()<<index;
    int p = stackWidget->duration ;

    if( index > 0){
        stackWidget->duration = stackWidget->duration/(2*(index-0));
        do{
            stackWidget->forward();
            QElapsedTimer t;
            t.start();
            while(t.elapsed()<2*stackWidget->duration)
                QCoreApplication::processEvents();
            index--;
        }while(index!=0);
    }
    stackWidget->duration = p;
    timer->start();

}
void Widget::on_button2_clicked()
{
    timer->stop();
        int index = stackWidget->currentIndex();
        int p = stackWidget->duration ;


        if( index > 1){
            stackWidget->duration = stackWidget->duration/(2*(index-1));
            do{
                stackWidget->forward();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index--;
            }while(index!=1);
        }
        else if(index = 0){
             stackWidget->duration = stackWidget->duration/2;
             stackWidget->next();
        }
        stackWidget->duration = p;
        timer->start();
}
void Widget::on_button3_clicked()
{
    timer->stop();
        int index = stackWidget->currentIndex();
        int p = stackWidget->duration ;


        if( index > 2){
            stackWidget->duration = stackWidget->duration/(2*(index-2));
            do{
                stackWidget->forward();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index--;
            }while(index!=2);
        }
        else if(index < 2){
            stackWidget->duration = stackWidget->duration/(2*(2-index));
            do{
                stackWidget->next();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index++;
            }while(index!=2);
        }
        stackWidget->duration = p;
        timer->start();

}
void Widget::on_button4_clicked()
{
    timer->stop();
        int index = stackWidget->currentIndex();
        int p = stackWidget->duration ;


        if( index > 3){
            stackWidget->duration = stackWidget->duration/(2*(index-3));
            do{
                stackWidget->forward();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index--;
            }while(index!=3);
        }
        else if(index < 3){
            stackWidget->duration = stackWidget->duration/(2*(3-index));
            do{
                stackWidget->next();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index++;
            }while(index!=3);
        }
        stackWidget->duration = p;
        timer->start();

}
void Widget::on_button5_clicked()
{
    timer->stop();
        int index = stackWidget->currentIndex();
        int p = stackWidget->duration ;


        if( index > 4){
            stackWidget->duration = stackWidget->duration/2;
            stackWidget->forward();
        }
        else if(index < 4){
            stackWidget->duration = stackWidget->duration/(2*(4-index));
            do{
                stackWidget->next();
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<2*stackWidget->duration)
                    QCoreApplication::processEvents();
                index++;
            }while(index!=4);
        }
        stackWidget->duration = p;
        timer->start();

}
void Widget::changecolor(){
    int index = stackWidget->currentIndex();
    if(index == 0){
        ui->button1->setStyleSheet("background-color: rgb(255,255,255);");
        ui->button2->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button3->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button4->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button5->setStyleSheet("background-color: rgb(0,0,0);");
    }
    if(index == 1){
        ui->button1->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button2->setStyleSheet("background-color: rgb(255,255,255);");
        ui->button3->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button4->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button5->setStyleSheet("background-color: rgb(0,0,0);");
    }
    if(index == 2){
        ui->button1->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button2->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button3->setStyleSheet("background-color: rgb(255,255,255);");
        ui->button4->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button5->setStyleSheet("background-color: rgb(0,0,0);");
    }
    if(index == 3){
        ui->button1->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button2->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button3->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button4->setStyleSheet("background-color: rgb(255,255,255);");
        ui->button5->setStyleSheet("background-color: rgb(0,0,0);");
    }
    if(index == 4){
        ui->button1->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button2->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button3->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button4->setStyleSheet("background-color: rgb(0,0,0);");
        ui->button5->setStyleSheet("background-color: rgb(255,255,255);");
    }
}
