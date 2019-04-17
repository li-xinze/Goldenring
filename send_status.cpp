#include"send_status.h"
#include <QtNetwork>
Send_Status::Send_Status()
{
    port = 4000;
    count = 1;
    sender = new QUdpSocket;
    model = "1.0";
}



void Send_Status::send(QString Identification,float Eye_x , float Eye_y, float Eye_z, float G_angle, float Moved)
{
    eye_x = QString("%1").arg(Eye_x);
    eye_y = QString("%1").arg(Eye_y);
    eye_z = QString("%1").arg(Eye_z);
    angle = QString("%1").arg(G_angle);
    moved = QString("%1").arg(Moved);
    status_list<<Identification<<model<<eye_x<<eye_y<<eye_z<<angle<<moved;
    status = status_list.join(",");
    QByteArray datagram = status.toUtf8();
    qDebug()<<"already send";
    sender->writeDatagram(datagram.data() , datagram.size(),
                          QHostAddress("58.87.88.169"),port);
    status_list.clear();
}

