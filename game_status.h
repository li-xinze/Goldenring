#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include <QWidget>
#include<QLabel>
#include<QDateTime>
#include<QGraphicsOpacityEffect>
namespace Ui {
class game_status;
}

class game_status : public QWidget
{
    Q_OBJECT

public:
    explicit game_status(QWidget *parent = 0);
    ~game_status();


private:
    //QLabel* datalabel;
    Ui::game_status *ui;

};

#endif // GAME_STATUS_H
