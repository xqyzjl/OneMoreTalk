#include "message.h"

#include<global/globaldata.h>

const QString MSG_SPLIT = GlobalData::MSG_SPLIT();
const QString MSG_DATA_SPLIT = GlobalData::MSG_DATA_SPLIT();

Message::Message()
{
    senderID=-1;
    receiverID=-1;
    datetime=QDateTime::currentDateTime();
    messageData="";
}

Message::Message(QString info)
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

Message::Message(QDateTime _datetime,QString _messageData,int _senderID,int _receiverID)
{
    datetime=_datetime;
    senderID=_senderID;
    receiverID=_receiverID;
    qDebug()<<datetime;
    messageData=QString(_messageData);
}


QString Message::toString() const{
    QString strSenderID=QString::number(senderID);
    QString strReceiverID=QString::number(receiverID);
    QString strDatetime=datetime.toString("yyyy-MM-dd hh:mm:ss");
    return  GlobalData::MSG_MSG_SPLIT()+
            strSenderID+MSG_SPLIT+
            strReceiverID+MSG_SPLIT+
            strDatetime+MSG_SPLIT+
            MSG_DATA_SPLIT+messageData;
}

int Message::getSenderID() const
{
    return senderID;
}

int Message::getReceiverID() const
{
    return receiverID;
}

QDateTime Message::getDatetime() const
{
    return datetime;
}

QString Message::getMessageData() const
{
    return messageData;
}

bool Message::valid() const{
    if(senderID==-1) return false;
    if(receiverID==-1) return false;
    return true;
}

QStringList Message::deCode() const{
    QStringList res = messageData.split(MSG_DATA_SPLIT);
//    qDebug() << messageData;
    res.pop_front();
//    qDebug() << res[0];
    res[0] = GlobalData::state2int(res[0]);
    return res;
}
