#include "status_reciver.h"
#include"send_status.h"

#include <QtNetwork>
using namespace  std ;

Status_Reciver::Status_Reciver()
{
    self_identify = "0";
    port =3000;
    count = 1;
    count_=0;
    A_status = new QMap<QString,QList<float> >;
    reciver = new QUdpSocket;
    connect(reciver, &QUdpSocket::readyRead, this, &Status_Reciver::processPendingDatagram);
    QByteArray request = "request for new port to connect";
    reciver->writeDatagram(request.data() , request.size(),
                          QHostAddress("58.87.88.169"),port);
}
void Status_Reciver::processPendingDatagram()
{
    qDebug()<<"have a message";
    while(reciver->hasPendingDatagrams())
    {
        QByteArray status;
        status.resize(reciver->pendingDatagramSize());
        reciver->readDatagram(status.data(), status.size());
        if(count == 1){
        port=status.toInt();
        count = 0;
        QByteArray connect = "new port get";
        reciver->writeDatagram(connect.data() , connect.size(),
                              QHostAddress("58.87.88.169"),port);
        self_identify = "2";
        }else{
        QString str = QString(status);
        QStringList rec_list = str.split(",",QString::SkipEmptyParts);
        QString identify;
        identify = rec_list[0];
        qDebug()<<"identity"<<identify;
        s1=rec_list[1].toFloat();           //model
        s2=rec_list[2].toFloat();           //x
        s3=rec_list[3].toFloat();           //y
        s4=rec_list[4].toFloat();           //z
        s5=rec_list[5].toFloat();            //水平角
        s6=rec_list[6].toFloat();            //状态
        if(identify != self_identify){
        if(!identify_list.contains(identify)){
            qDebug()<<"add";
            identify_list.append(identify);
            status_info.clear();
            status_info.push_back(s1);
            status_info.push_back(s2);
            status_info.push_back(s3);
            status_info.push_back(s4);
            status_info.push_back(s5);
            status_info.push_back(s6);
            A_status->insert(identify,status_info);
        }
        else{
            status_info.clear();
            status_info.push_back(s1);
            status_info.push_back(s2);
            status_info.push_back(s3);
            status_info.push_back(s4);
            status_info.push_back(s5);
            status_info.push_back(s6);
            A_status->insert(identify,status_info);
        }
        }
        }
        count_++;
        qDebug()<<count_;
    }
}

bool Status_Reciver::set_player_status(QString Identification,float *model,float *Eye_x , float *Eye_y, float *Eye_z, float *G_angle, float *Moved){

    QMap<QString,QList<float> >::iterator i=A_status->find(Identification);
    QList<float>list =i.value();
    *model = list[0];
    *Eye_x = list[1];
    *Eye_y = list[2];
    *Eye_z = list[3];
    *G_angle = list[4];
    *Moved = list[5];
}


