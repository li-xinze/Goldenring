#include "qanimationstackedwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QPixmap>

QAnimationStackedWidget::QAnimationStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    isAnimation = false;
    //设置默认的时间间隔
    duration = 1000;
    //初始化animation框架、并连接信号和槽
    animation = new QPropertyAnimation(this, QByteArray());
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged_slot(QVariant)));
    connect(animation, SIGNAL(finished()), this, SLOT(animationFinished()));
}
void QAnimationStackedWidget::setDuration(int d)
{
    duration = d;
}
void QAnimationStackedWidget::paintEvent(QPaintEvent *e)
{
    if( isAnimation )
    {
        QPainter paint(this);
        switch( direction )
        {
        case LeftToRight:
            //绘制当前Widget
            paintPrevious(paint, currentIndex());
            //绘制下一个widget
            paintNext(paint, nextIndex);
            break;
        case RightToLeft:
            //绘制当前Widget
            paintPrevious(paint, nextIndex);
            //绘制下一个widget
            paintNext(paint, currentIndex());
            break;
        }
    }
}
void QAnimationStackedWidget::paintPrevious(QPainter &paint, int currentIndex)
{
    //获得当前页面的Widget
    QWidget *w = widget(currentIndex);
    QPixmap pixmap(w->size());
    //将Widget的内容渲染到QPixmap对象中，即将Widget变成一张图片
    w->render(&pixmap);
    QRect r = w->geometry();
    //绘制当前的Widget
    double value = currentValue.toDouble();
    QRectF r1(0.0, 0.0, value, r.height());
    QRectF r2(r.width() - value, 0, value, r.height());
    paint.drawPixmap(r1, pixmap, r2);
}
void QAnimationStackedWidget::paintNext(QPainter &paint, int nextIndex)
{
    QWidget *nextWidget = widget(nextIndex);
    QRect r = geometry();
    nextWidget->resize(r.width(), r.height());
    QPixmap nextPixmap(nextWidget->size());
    nextWidget->render(&nextPixmap);
    double value = currentValue.toDouble();
    QRectF r1(value, 0.0, r.width() - value, r.height());
    QRectF r2(0.0, 0.0, r.width() - value, r.height());
    paint.drawPixmap(r1, nextPixmap, r2);
}
void QAnimationStackedWidget::valueChanged_slot(QVariant value)
{
    currentValue = value;
    update();
}
void QAnimationStackedWidget::animationFinished()
{
    isAnimation = false;
    widget(currentIndex())->show();
    setCurrentIndex(nextIndex);

}
void QAnimationStackedWidget::next()
{
    if( isAnimation )
    {
        return;
    }
    isAnimation = true;
    widgetCount = count();
    int c = currentIndex();
    nextIndex = (c + 1) % widgetCount;
    direction = LeftToRight;
    //隐藏当前的widget
    widget(c)->hide();
    //开始动画并设置间隔和开始、结束值
    QRect g = geometry();
    int x = g.x();
    int width = g.width();
    animation->setStartValue(width);
    animation->setEndValue(0);
    animation->setDuration(duration);
    animation->start();
}
void QAnimationStackedWidget::forward()
{

    if( isAnimation )
    {
        return;
    }
    isAnimation = true;
    int c = currentIndex();
    widgetCount = count();
    nextIndex = (c + widgetCount - 1) % widgetCount;
    direction = RightToLeft;
                          //隐藏当前的widget
    widget(c)->hide();
    //开始动画并设置间隔和开始、结束值
    QRect g = geometry();
    int x = g.x();
    int width = g.width();
    animation->setStartValue(0);
    animation->setEndValue(width);
    animation->setDuration(duration);
    animation->start();
}
QAnimationStackedWidget::~QAnimationStackedWidget()
{
    if( animation )
    {
        delete animation;
        animation = NULL;
    }
}
