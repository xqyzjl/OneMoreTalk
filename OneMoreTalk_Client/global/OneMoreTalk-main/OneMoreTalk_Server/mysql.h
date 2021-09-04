#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <historymessage.h>
#include <publicinfo.h>
#include <groupinfo.h>

/**********************************************************
 * 数据库：sqlite
 * 用户信息表：usersInfo (userId int PRIMARYKEY UNIQUE,
 *                      password text,
 *                      userName text,
 *                      userImg int,
 *                      userQ text,
 *                      userA text,
 *                      userLabel text,
 *                      userAge int,
 *                      userSex int)
 *
 * 用户好友表：friend+[userID] (friendId INT UNIQUE)
 *
 * 用户群聊表：usergroup+[userID] (groupId INT UNIQUE)
 *
 * 群聊成员表：group+[groupID] (userId INT UNIQUE)
 *
 * 私聊消息记录表：p2pmsg+[userID1]+"_"+[userID2] (TM time,
 *                                              senderId INT,
 *                                              Msg TEXT)
 *
 * 群聊消息记录表：groupmsg+[groupID] (TM time,
 *                                  senderId INT,
 *                                  Msg TEXT)
 *
 **********************************************************/

class MySql : public QObject
{
    Q_OBJECT
public:
    static MySql* gethand() {
        if(sqlhand == nullptr) {
            sqlhand = new MySql();
        }
        return sqlhand;
    }

    void openDatabase();

    bool createTableUserInfo(QString tablename); // userInfo
    bool createTableFriend(int id); // friend
    bool createTableUserGroup(int id); // group
    bool createTableGroup(int id); // group
    bool createTableP2PMsg(int id1, int id2); // p2pmsg
    bool createTableGroupMsg(int id); // groupmsg

    // 用参数直接insert用户信息
    bool insertUsersInfo (int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel = "", int userage = 0, int usersex = 0);
    // 用AllInfo类insert用户信息
    bool insertUsersInfo (AllInfo info);
    // 用参数直接insert好友信息，并创建私聊数据表
    void insertUserFriend (int userid, int friendid);
    // 用参数直接insert群聊信息
    void insertGroupUser (int groupid, QList<int> userid);
    // 用GroupInfo类insert群聊信息
    void insertGroupUser (GroupInfo info);
    // 用参数直接insert私聊msg
    void insertP2PMsg (int senderid, int receiverid, QString tm, QString msg);
    // 用Message类insert私聊msg
    void insertP2PMsg (HistoryMessage msg);
    // 用参数直接insert群聊msg
    bool insertGroupMsg (int groupid, int senderid, QString tm, QString msg);
    // 用Message类insert群聊msg
    bool insertGroupMsg (HistoryMessage msg);
    // 新建一个群聊，创建群聊信息表 & 群聊历史记录表
    void insertGroup(int groupid);

    // 查询用户的公开信息，返回PublicInfo类
    PublicInfo selectUserPublicInfo (int userid);
    // 查询用户的好友信息，返回PublicInfo类的List
    QList<PublicInfo> selectFriendInfo(int userid);
    // 查询用户的群聊信息，返回int类的List
    QList<int> selectUserGroupInfo(int userid);
    // 查询群聊的用户信息，返回PublicInfo类的List
    QList<PublicInfo> selectGroupInfo(int groupid);
    // 查询用户的所有信息（包括公共、私有），返回AllInfo类
    AllInfo selectUserAllInfo (int userid);
    // 查询sender与receiver的私聊历史，返回Message类的List
    QList<HistoryMessage> selectP2PMsg (int senderid, int receiverid);
    // 查询群聊的聊天历史，返回Message类的List
    QList<HistoryMessage> selectGroupMsg (int groupid);

    // 删除用户
    void deleteUserInfo (int userid);
    // 删除用户的一个好友（单纯删除好友，不删除聊天记录）
    void deleteUserFriend(int userid, int friendid);
    // 删除群聊中的一个用户
    void deleteGroupUser(int groupid, QList<int> userid);
    // 删除用户的一个好友，同时删除两人聊天记录
    void dropFriend (int userid, int friendid);
    // 删除一个群聊，同时删除聊天记录
    void dropGroup (int groupid);

    // 更新用户信息（原理：delete + insert）
    bool updateUsersInfo (int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel, int userage, int usersex);

private:
    explicit MySql(QObject *parent = nullptr);
    static MySql* sqlhand;
    QSqlDatabase database;
    QSqlQuery* sqlquery;
    QStringList tablelist;
    bool execInsertSql(QString sqlsentence);
signals:

};

#endif // MYSQL_H
