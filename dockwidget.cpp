#include "dockwidget.h"
#include "ui_dockwidget.h"

DockWidget::DockWidget(QWidget *parent) :
    QDockWidget(parent)
{


    datalabel = new QLabel(this);
    QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
    datalabel->setText(datatime->time().toString());
    datalabel->show();
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    this->setGraphicsEffect(opacityEffect);
    datalabel->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.0);




}
