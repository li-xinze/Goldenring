#ifndef STATUS_RECIVER_H
#define STATUS_RECIVER_H
#include"status_reciver.h"
#include <QDialog>
#include<string>

class QUdpSocket;
class Status_Reciver : public QObject
{
     Q_OBJECT
public:
    Status_Reciver();
     QList<QString>identify_list;
    int get_player_number();
    bool set_player_status(QString Identification, float *model, float *Eye_x, float *Eye_y, float *Eye_z, float *G_angle, float *Moved);
    QString get_self_identify(){
        return self_identify;
    }
private slots:
    void processPendingDatagram();
private:
    QUdpSocket *reciver;
    float s1,s2,s3,s4,s5,s6;
    int port,count,count_,A_status_count;
    QString self_identify;
    QMap<QString,QList<float> > *A_status;
    QList<float> status_info;
};

#endif // STATUS_RECIVER_H
