#include "game_status.h"
#include "ui_game_status.h"


game_status::game_status(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_status)
{
    ui->setupUi(this);
    ui->datalabel;
    QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
    ui->datalabel->setText(datatime->time().toString("HH:mm"));
    QFont font("Microsoft YaHei", 20);
    font.setBold(true);
    ui->datalabel->setFont(font);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    ui->datalabel->setPalette(pe);
    pe.setColor(QPalette::Window,Qt::white);
    ui->datalabel->setPalette(pe);
    ui->datalabel->show();
    this->setWindowOpacity(0);
    this->setWindowFlags(Qt::FramelessWindowHint);
}
game_status::~game_status()
{
    delete ui;
}



