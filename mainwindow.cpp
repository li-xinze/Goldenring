#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsColorizeEffect>
#include<QToolButton>
#include<QMessageBox>
#include<qdesktopservices.h>
#define MAP 40

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    tcpSocket = new QTcpSocket(this);
    ui->setupUi(this);
    initWidgets();
    //this->setWindowFlags(Qt::Window);
    //this->showFullScreen();
    mode = true;  //overall view
    QPalette pe;
    pe.setColor(QPalette::Window,Qt::white);
    this->setPalette(pe);
    QToolButton *minButton = new QToolButton(this);   //最小按钮
    QToolButton *closeButton= new QToolButton(this);  //关闭按钮
    QPixmap min_pix(":/login/pic/little.png");
    min_pix= min_pix.scaled(QSize(wid*1/30,wid*1/30));
    minButton->move(wid*8/15,0);
    minButton->setMask(min_pix.mask());
    minButton->setStyleSheet("QPushButton{border-image:url(:/login/pic/little.png);}");
    minButton->setFixedSize(min_pix.size());
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    int width_ = this->width();
    minButton->setGeometry(width_-120,0,20,20);
    closeButton->setGeometry(width_-100,0,20,20);
    connect(minButton, SIGNAL(clicked()), this, SLOT(on_actionMinimize_triggered()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(on_actionClose_triggered()));
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readMessage);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}
void MainWindow::initWidgets()
{
    int wid =QApplication::desktop()->width();
    int hei = wid * 2/3;
    setGeometry(wid*1/5,hei*1/5,wid*3/5,hei*3/5);
//mainchoice最上方菜单栏
    ui->main_choice->setGeometry(wid*3/45,hei*1/30,wid*24/45,hei*1/12);              //最上方菜单选择栏
    QPixmap pixmap1(":/login/pic/pic1.png");
    pixmap1 = pixmap1.scaled(QSize(wid*1/8, hei*1/17));
    ui->option1->setMask(pixmap1.mask());
    ui->option1->setStyleSheet("QPushButton{border-image:url(:/login/pic/pic1.png);}"
        "QPushButton:hover{border-image:url(:/login/pic/pic1_.png);}"
        "QPushButton:pressed{border-image:url(:/login/pic/pic1_d.png);}");
    ui->option1->setFixedSize(pixmap1.size());

    QPixmap pixmap2(":/login/pic/pic2.png");
    pixmap2 = pixmap2.scaled(QSize(wid*1/8, hei*1/17));
    ui->option2->setMask(pixmap2.mask());
    ui->option2->setStyleSheet("QPushButton{border-image:url(:/login/pic/pic2.png);}"
        "QPushButton:hover{border-image:url(:/login/pic/pic2_.png);}"
        "QPushButton:pressed{border-image:url(:/login/pic/pic2_d.png);}");
    ui->option2->setFixedSize(pixmap2.size());

    QPixmap pixmap3(":/login/pic/pic3.png");
    pixmap3 = pixmap3.scaled(QSize(wid*1/8, hei*1/17));
    ui->option3->setMask(pixmap3.mask());
    ui->option3->setStyleSheet("QPushButton{border-image:url(:/login/pic/pic3.png);}"
        "QPushButton:hover{border-image:url(:/login/pic/pic3_.png);}"
        "QPushButton:pressed{border-image:url(:/login/pic/pic3_d.png);}");
    ui->option3->setFixedSize(pixmap3.size());

    QPixmap pixmap4(":/login/pic/pic4.png");
    pixmap4 = pixmap4.scaled(QSize(wid*1/8, hei*1/17));
    ui->option4->setMask(pixmap4.mask());
    ui->option4->setStyleSheet("QPushButton{border-image:url(:/login/pic/pic4.png);}"
        "QPushButton:hover{border-image:url(:/login/pic/pic4_.png);}"
        "QPushButton:pressed{border-image:url(:/login/pic/pic4_d.png);}");
    ui->option4->setFixedSize(pixmap4.size());

//动画窗口
    animation_widget = new Widget(this);
    //animation_widget->setGeometry(wid*1/30,hei*1/12,wid*1/4,hei*1/4);
    animation_widget->setGeometry(wid*2/30,hei*4/30,wid*7/30,hei*1/5);


    animation_widget->show();
//登陆窗口
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::black);
    ui->lineEdit_accout->setPalette(palette);
    ui->lineEdit_key->setPalette(palette);
    //ui->lineEdit_accout->setStyleSheet(QString(":focus{ background-color: grey; }"));

    QGraphicsOpacityEffect *opacityEffect_1=new QGraphicsOpacityEffect;
    opacityEffect_1->setOpacity(0.3);
    ui->lineEdit_accout->setGraphicsEffect(opacityEffect_1);
    QGraphicsOpacityEffect *opacityEffect_2=new QGraphicsOpacityEffect;
    opacityEffect_2->setOpacity(0.3);
    ui->lineEdit_key->setGraphicsEffect(opacityEffect_2);

    ui->zhanghao->setStyleSheet("color:#FFFFF0");
    ui->mima->setStyleSheet("color:#FFFFF0");
    ui->checkBox->setStyleSheet("color:#FFFFF0");
    ui->zhuce->setStyleSheet("color:#FFFFF0");

    ui->wangji->setStyleSheet("color:#FFFFF0");
    ui->login->setGeometry(wid*9/40,hei*23/60,wid*3/20,hei*1/5);
    //ui->zhanghao->resize(wid*1/20,hei*1/15);
    ui->enter_game->resize(wid*1/10,hei*1/30);
    QPixmap pixmap0(":/login/pic/enter.png");
    pixmap0 = pixmap0.scaled(QSize(wid*1/8, hei*1/13));
    ui->enter_game->move(wid*12/30,hei*23/60);
    ui->enter_game->setMask(pixmap0.mask());
    ui->enter_game->setStyleSheet("QPushButton{border-image:url(:/login/pic/enter.png);}"
        "QPushButton:hover{border-image:url(:/login/pic/enter_.png);}");

    ui->enter_game->setFixedSize(pixmap0.size());
   /* ui->enter_game->setStyleSheet("QPushButton{background-color:black;\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;}"
                                "QPushButton:hover{background-color:white; color: black;}"
                                "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                border-style: inset; }" );*/
//logo
    QPixmap pixmap_logo(":/login/pic/logo.png");
    pixmap_logo = pixmap_logo.scaled(QSize(wid*1/8, hei*1/15));
    ui->logo->move(wid*18/40,hei*29/60);
    ui->logo->setMask(pixmap_logo.mask());
    ui->logo->setStyleSheet("QLabel{border-image:url(:/login/pic/logo.png);}");
    ui->logo->setFixedSize(pixmap_logo.size());

    QPixmap pixmap_logo1(":/login/pic/logo1.png");

    pixmap_logo1 = pixmap_logo1.scaled(QSize(wid*1/8, hei*1/35));
    ui->logo1->move(wid*18/40,hei*33/60);
    ui->logo1->setMask(pixmap_logo1.mask());
    ui->logo1->setStyleSheet("QLabel{border-image:url(:/login/pic/logo1.png);}");
    ui->logo1->setFixedSize(pixmap_logo1.size());

//新闻公告
     ui->frame_down->raise();
     ui->frame_down->show();
     ui->frame_down->setGeometry(wid*1/3,hei*4/30,wid*7/30,hei*1/5);
     //QPalette palette;
     //palette.setColor(QPalette::Text,Qt::yellow);
     //ui->text1->setPalette(palette);
     QPixmap pixmap_new(":/login/pic/gonggao.png");
     pixmap_new = pixmap_new.scaled(QSize(wid*1/13, hei*1/32));
     ui->gonggao->setMask(pixmap_new.mask());
     ui->gonggao->setStyleSheet("QLabel{border-image:url(:/login/pic/gonggao.png);}");

     ui->gonggao->setFixedSize(pixmap_new.size());
     QPixmap pixmap_m(":/login/more.png");
     pixmap_m = pixmap_m.scaled(QSize(wid*1/19, hei*1/38));
     ui->more->setMask(pixmap_m.mask());
     ui->more->setStyleSheet("QPushButton{border-image:url(:/login/pic/more.png);}"
         "QPushButton:hover{border-image:url(:/login/pic/more_.png);}"
         "QPushButton:pressed{border-image:url(:/login/pic/more_d.png);}");
     ui->more->setFixedSize(pixmap_m.size());
     ui->text1->setText("» [新闻]<金环小镇>新服开启充值优惠");
     ui->text2->setText("» [新闻]<金环小镇>游戏攻略");
     ui->text3->setText("» [新闻]<金环小镇>BUG提交有奖");
     ui->text4->setText("» [新闻]玩家心情日志");
     ui->text5->setText("» [新闻]玩家owen.x游戏心得");
     ui->text1->setStyleSheet("color: white");
     ui->text2->setStyleSheet("color: white");
     ui->text3->setStyleSheet("color: white");
     ui->text4->setStyleSheet("color: white");
     ui->text5->setStyleSheet("color: white");
     ui->text1_->setStyleSheet("QPushButton{text-align : right;color: white}");
     ui->text2_->setStyleSheet("QPushButton{text-align : right;color: white}");
     ui->text3_->setStyleSheet("QPushButton{text-align : right;color: white}");
     ui->text4_->setStyleSheet("QPushButton{text-align : right;color: white}");
     ui->text5_->setStyleSheet("QPushButton{text-align : right;color: white}");
     ui->text1_->setText("4/24");
     ui->text2_->setText("4/24");
     ui->text3_->setText("4/24");
     ui->text4_->setText("4/24");
     ui->text5_->setText("4/24");

//游戏主界面

//作者信息
    ui->message_author->setGeometry(wid*13/60,hei*43/80,wid*1/5,hei*3/80);
    ui->message_author->setStyleSheet("color:white");

//图形装饰
    QPixmap pixmap_c(":/login/pic/church.png");
    pixmap_c = pixmap_c.scaled(QSize(wid*5/30,hei*3/10));
    ui->church->setMask(pixmap_c.mask());
    ui->church->setStyleSheet("QPushButton{border-image:url(:/login/pic/church.png);}");
    ui->church->setFixedSize(pixmap_c.size());
    ui->church->move(wid*1/30,hei*19/60);
    ui->church->raise();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Window);
    this->setFocus();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_enter_game_clicked()
{
    //QString username = ui->lineEdit_accout->text();
    //QString password = ui->lineEdit_key->text();
    //newConnect(username,password);
    readMessage();
}
void MainWindow::paintEvent(QPaintEvent* event){
    QPixmap pixmap = QPixmap(":/login/pic/1.png").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(),pixmap);
}
void MainWindow::on_actionMinimize_triggered()
{
    //系统自定义的最小化窗口函数
    showMinimized();
}
void MainWindow::on_actionClose_triggered()
{
    //系统自定义的窗口关闭函数
    close();
}
void MainWindow::on_zhuce_clicked()
{
    QDesktopServices::openUrl(QUrl("http://39.105.70.124:8080/test/register.html"));
}
void MainWindow::readMessage()
{
    /*QByteArray qdb = tcpSocket->readAll();
    QString text = QVariant(qdb).toString();
    if(text == "1"){
        return_value= 1;
    }
    if(text == "2"){
        return_value= 2;
    }
    if(text == "0"){
        return_value= 0;
    }

    if( return_value == 1){
        QMessageBox::warning(this,tr("登陆信息"),
                             tr("该账号未注册"),QMessageBox::tr("返回"));
    }
    if(return_value == 2){
        QMessageBox::critical(this,tr("登陆信息"),
                             tr("密码错误,请重新输入"),QMessageBox::tr("返回"));
    }
    if(return_value == 3){
        QMessageBox::warning(this,tr("登陆信息"),
                             tr("网络错误"),QMessageBox::tr("返回"));
    }
    if(return_value ==4){
        QMessageBox::warning(this,tr("登陆信息"),
                             tr("服务器超时"),QMessageBox::tr("返回"));
    }
    if(return_value == 0){*/
    delete this;
    glArea = new glWidget;
    //close();
    glArea->show();
    glArea->setWindowFlags(Qt::Window);
   glArea->showFullScreen();
    glArea->setFocus();
    glArea->setMouseTracking(true);

    //}
}
void MainWindow::newConnect(QString username,QString password )
{

    tcpSocket->abort();
    tcpSocket->connectToHost("39.105.70.124",9000);
    QString  str = username+"="+password;
    QByteArray ba = str.toUtf8();
    tcpSocket->write(ba);

}
void MainWindow::displayError(QAbstractSocket::SocketError)
{

   QString error = tcpSocket->errorString();
   qDebug()<<"ddd";
   if(error != "The remote host closed the connection"){
       return_value=3;
   }
}
void MainWindow::focusInEvent(QFocusEvent *e)
{
    QGraphicsOpacityEffect *opacityEffect_1=new QGraphicsOpacityEffect;
    opacityEffect_1->setOpacity(1.0);
    ui->lineEdit_accout->setGraphicsEffect(opacityEffect_1);

       QPalette p=QPalette();
       p.setColor(QPalette::Base,Qt::gray);    //QPalette::Base 对可编辑输入框有效，还有其他类型，具体的查看文档
       ui->lineEdit_accout->setPalette(p);
}
void MainWindow::focusOutEvent(QFocusEvent *e){
    QGraphicsOpacityEffect *opacityEffect_1=new QGraphicsOpacityEffect;
    opacityEffect_1->setOpacity(0.3);
    ui->lineEdit_accout->setGraphicsEffect(opacityEffect_1);


}
void MainWindow::on_lineEdit_key_returnPressed()
{
    on_enter_game_clicked();
}
