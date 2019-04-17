#ifndef SEND_STATUS_H
#define SEND_STATUS_H
#include<Qstring>
#include<QStringList>
using namespace std;
class QUdpSocket;
class Send_Status
{
public:
    Send_Status();
    void send(QString Identification,float Eye_x , float Eye_y, float Eye_z, float G_angle, float Moved);


private:
    QUdpSocket *sender;
    int port;
    int count;
    QString status;
    QString model;
    QString eye_x ;
    QString eye_y ;
    QString eye_z ;
    QString angle ;
    QString moved;
    QStringList status_list;
};

#endif // SEND_STATUS_H
