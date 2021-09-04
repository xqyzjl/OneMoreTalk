#ifndef HISTORYMESSAGE_H
#define HISTORYMESSAGE_H

#include<QString>
#include<QDateTime>
#include<QDebug>

class HistoryMessage{
public:
    QString toString() const;
    bool valid() const;
    HistoryMessage();
    HistoryMessage(QString info);
    HistoryMessage(QDateTime _datetime,QString _messageData,int _senderID,int _receiverID);
    int getSenderID() const;
    int getReceiverID() const;
    QDateTime getDatetime() const;
    QString getMessageData() const;
private:
    int senderID;
    int receiverID;
    QDateTime datetime;
    QString messageData;
};

#endif // HISTORYMESSAGE_H
