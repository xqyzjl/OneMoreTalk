#ifndef MESSAGE_H
#define MESSAGE_H

#include<QString>
#include<QDateTime>
#include<QDebug>

class Message{
public:
    QString toString() const;
    bool valid() const;
    Message();
    Message(QString info);
    Message(QDateTime _datetime,QString _messageData,int _senderID,int _receiverID);
    int getSenderID() const;
    int getReceiverID() const;
    QDateTime getDatetime() const;
    QString getMessageData() const;
    QStringList deCode() const;
private:
    int senderID;
    int receiverID;
    QDateTime datetime;
    QString messageData;
};

#endif // MESSAGE_H
