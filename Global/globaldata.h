#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#define SIGNUP_QUEST 1
#define SIGNUP_OK 2
#define LOGIN_QUEST 3
#define LOGIN_OK 4
#define PASSWORD_FIND 5
#define PASSWORD_PROTECT_ANSWER 6
#define PASSWORD_PROTECT_QUESTION 7
#define PASSWORD_FIND_OK 8
#define MESSAGE 9
#define SEND_OK 10
#define RECEIVE_OK 12
#define SIGNUP_USER_INFO_REQUEST 13
#define GROUP_INFO_REQUEST 14
#define FRIEND_INFO 15
#define GROUP_INFO 16
#define FRIEND_HISTORY_REQUEST 17
#define GROUP_HISTORY_REQUEST 18
#define FRIEND_HISTORY 19
#define GROUP_HISTORY 20
#define FRIENDS_INFO_REQUEST 21
#define GROUPS_INFO_REQUEST 22
#define FRIENDS_INFO 23
#define GROUPS_INFO 24
#define FRIEND_ADD_REQUEST 25
#define FRIEND_ADD_OK 26
#define FRIEND_REMOVE_REQUEST 27
#define FRIEND_REMOVE_OK 28
#define GROUP_ADD_REQUEST 29
#define GROUP_ADD_OK 30
#define GROUPUSER_REMOVE_REQUEST 31
#define GROUPUSER_REMOVE_OK 32
#define USER_INFO_UPDATE_REQUEST 33
#define USER_INFO_UPDATE_OK 34
#define ERROR -1

#define CLOUD 0



#include<QString>
#include<QMap>
#include<QHash>
#include<global/publicinfo.h>
#include<global/groupinfo.h>
#include<QDateTime>

class GlobalData
{
public:
    static QString SPLIT();
    static QString MSG_SPLIT();
    static QString MSG_DATA_SPLIT();
    static QString MSG_MSG_SPLIT();
    static QString state2int(QString);
    static int MyId;
    static QHash<int,PublicInfo*> id2PInfo;
    static QHash<int,GroupInfo*> id2GInfo;
    static void* get_mainWindow();
    static void* get_loginWindow();
    static void* get_infoWindow();
    static void* get_forgetWindow();
    static void* get_signupWindow();
private:
    static QMap<QString,QString> __state2int;
    static QMap<int,QString> __int2state;
    static void *mainwindow;
    static void *loginwindow;
    static void *infowindow;
    static void *forgetwindow;
    static void *signupwindow;


public:
    static void sleep(unsigned int msec) {
        QTime reachtime = QTime::currentTime().addMSecs(msec);
        while(QTime::currentTime() < reachtime);
        return;
    }
};
#endif // GLOBALDATA_H
