#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include<QLabel>
#include<QDateTime>
#include<QGraphicsOpacityEffect>



class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
     DockWidget(QWidget *parent = 0);
    //~DockWidget();

private:
    QLabel* datalabel ;

};

#endif // DOCKWIDGET_H
