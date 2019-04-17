#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QTimer>
#include <QBitmap>
#include <QMainWindow>
#include <QLabel>
#include "glwidget.h"
#include "game_status.h"
#include "widget.h"
#include<QtNetwork>
class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initWidgets();
    game_status* G_status;
   void focusInEvent(QFocusEvent *e);
   void focusOutEvent(QFocusEvent *e);
private slots:
    void on_enter_game_clicked();
    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口
    void on_zhuce_clicked();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
    void on_lineEdit_key_returnPressed();

private:

    QTcpSocket *tcpSocket;
    int return_value = 4;
    int wid,hei;
    bool mode;
    Ui::MainWindow *ui;
    glWidget* glArea;
    Widget* animation_widget;
    QLabel* sidebar;
    QLabel *pMode,*pScale,*pXangle,*pYangle;
    void paintEvent(QPaintEvent* event);
    void newConnect(QString username,QString password );

};

#endif // MAINWINDOW_H
