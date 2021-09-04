#include "historymessage.h"
//OvO
#include<globaldata.h>

const QString MSG_SPLIT = GlobalData::MSG_SPLIT();
const QString MSG_DATA_SPLIT = GlobalData::MSG_DATA_SPLIT();

HistoryMessage::HistoryMessage()
{
    senderID=-1;
    receiverID=-1;
    datetime=QDateTime::currentDateTime();
    messageData="";
}

HistoryMessage::HistoryMessage(QString info)
{
    senderID=info.section(MSG_SPLIT,0,0).toInt();
    receiverID=info.section(MSG_SPLIT,1,1).toInt();
    QStringList strDatetime=info.section(MSG_SPLIT,2,2).split(' ');
    QString strDate = strDatetime[0],strTime = strDatetime[1];

    int y=strDate.section('-',0,0).toInt();
    int M=strDate.section('-',1,1).toInt();
    int d=strDate.section('-',2,2).toInt();
    int h=strTime.section(':',0,0).toInt();
    int m=strTime.section(':',1,1).toInt();
    int s=strTime.section(':',2,2).toInt();
    datetime=QDateTime(QDate(y,M,d),QTime(h,m,s));
    messageData=info.section(MSG_SPLIT,3);
}

HistoryMessage::HistoryMessage(QDateTime _datetime,QString _messageData,int _senderID,int _receiverID)
{
    datetime=_datetime;
    senderID=_senderID;
    receiverID=_receiverID;
    datetime=QDateTime::currentDateTime();
    qDebug()<<datetime;
    messageData=QString(_messageData);
}


QString HistoryMessage::toString() const{
    QString strSenderID=QString::number(senderID);
    QString strReceiverID=QString::number(receiverID);
    QString strDatetime=datetime.toString("yyyy-MM-dd hh:mm:ss");
    return strSenderID+MSG_SPLIT+
           strReceiverID+MSG_SPLIT+
           strDatetime+MSG_SPLIT+
           MSG_DATA_SPLIT+messageData;
}

int HistoryMessage::getSenderID() const
{
    return senderID;
}

int HistoryMessage::getReceiverID() const
{
    return receiverID;
}

QDateTime HistoryMessage::getDatetime() const
{
    return datetime;
}

QString HistoryMessage::getMessageData() const
{
    return messageData;
}

bool HistoryMessage::valid() const{
    if(senderID==-1) return false;
    if(receiverID==-1) return false;
    return true;
}
