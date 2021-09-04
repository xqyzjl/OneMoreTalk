#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <tcpserver.h>
#include <QMap>
#include <mysql.h>
#include <globaldata.h>
#include <message.h>
#include <QStringList>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(QObject *parent = nullptr);

signals:
private slots:
    void slot_handleMsg(QString strmsg, QTcpSocket* socket);
private:
    TcpServer* myTcphand;
    MySql* mySqlhand;
    QMap<int, QTcpSocket*> IDMap;
    int nextID;

    void IS_SIGNUP_QUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_SIGNUP_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_LOGIN_QUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_LOGIN_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_PASSWORD_FIND(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_PASSWORD_PROTECT_ANSWER(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_PASSWORD_FIND_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_PASSWORD_PROTECT_QUESTION(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_ERROR(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_USER_INFO_UPDATE_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_USER_INFO_UPDATE_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUPUSER_REMOVE_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_ADD_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUPUSER_REMOVE_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_ADD_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_REMOVE_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_REMOVE_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_ADD_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUPS_INFO(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_ADD_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIENDS_INFO(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_HISTORY(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUPS_INFO_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIENDS_INFO_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_HISTORY_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_HISTORY(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_INFO(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_HISTORY_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_MESSAGE(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_SEND_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_SIGNUP_USER_INFO_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_RECEIVE_OK(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_GROUP_INFO_REQUEST(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;
    void IS_FRIEND_INFO(QStringList &msg, int sender, int receiver, QDateTime dt, QTcpSocket* socket) ;

    void sendMessage(QTcpSocket*, Message);
signals :
    void sig_display_activity(QString);

private slots:
    void slot_clientLogOut(QTcpSocket *);
};

#endif // SERVERMANAGER_H
