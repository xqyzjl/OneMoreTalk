#ifndef CLOUD_H
#define CLOUD_H

#include <QObject>
#include <QTcpSocket>
#include <global/message.h>
#include <global/globaldata.h>

class Cloud: public QObject{
    Q_OBJECT
public:
    Cloud();
    bool set(const QString &IP,int port);
    static Cloud* gethand();
    void send(int sender,int receiver,const QString &msg_data);
    void sendFriendInfoRequest(int userID);
    void sendFriendHistoryRequest(int userID);
private:
    static Cloud *myhand;
    QTcpSocket socket;
    void read(QString msg);
private slots:
    void slot_fakeread();
public:
    void SIG_FRIEND_INFO(const Message &msg);
    void SIG_GROUP_INFO(const Message &msg);
signals:
    void SIG_SIGNUP_QUEST(const Message &msg);
    void SIG_SIGNUP_OK(const Message &msg);
    void SIG_LOGIN_QUEST(const Message &msg);
    void SIG_LOGIN_OK(Message);
    void SIG_PASSWORD_FIND(const Message &msg);
    void SIG_PASSWORD_PROTECT_ANSWER(const Message &msg);
    void SIG_PASSWORD_PROTECT_QUESTION(const Message &msg);
    void SIG_PASSWORD_FIND_OK(const Message &msg);
    void SIG_MESSAGE(const Message &msg);
    void SIG_SEND_OK(const Message &msg);
    void SIG_RECEIVE_OK(const Message &msg);
    void SIG_SIGNUP_USER_INFO_REQUEST(const Message &msg);
    void SIG_GROUP_INFO_REQUEST(const Message &msg);
    void SIG_FRIEND_HISTORY_REQUEST(const Message &msg);
    void SIG_GROUP_HISTORY_REQUEST(const Message &msg);
    void SIG_FRIEND_HISTORY(const Message &msg);
    void SIG_GROUP_HISTORY(const Message &msg);
    void SIG_FRIENDS_INFO_REQUEST(const Message &msg);
    void SIG_GROUPS_INFO_REQUEST(const Message &msg);
    void SIG_FRIENDS_INFO(const Message &msg);
    void SIG_GROUPS_INFO(const Message &msg);
    void SIG_FRIEND_ADD_REQUEST(const Message &msg);
    void SIG_FRIEND_ADD_OK(const Message &msg);
    void SIG_FRIEND_REMOVE_REQUEST(const Message &msg);
    void SIG_FRIEND_REMOVE_OK(const Message &msg);
    void SIG_GROUP_ADD_REQUEST(const Message &msg);
    void SIG_GROUP_ADD_OK(const Message &msg);
    void SIG_GROUPUSER_REMOVE_REQUEST(const Message &msg);
    void SIG_GROUPUSER_REMOVE_OK(const Message &msg);
    void SIG_USER_INFO_UPDATE_REQUEST(const Message &msg);
    void SIG_USER_INFO_UPDATE_OK(const Message &msg);
    void SIG_ERROR(const Message &msg);
};

#endif // CLOUD_H
