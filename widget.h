#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qanimationstackedwidget.h>
#include<QTimer>
#include<QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void changecolor();

private:
    QTimer * timer;
    QTimer * timer2;
    Ui::Widget *ui;
    QAnimationStackedWidget *stackWidget;
};

#endif // WIDGET_H
