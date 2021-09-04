#include "mysql.h"
MySql* MySql::sqlhand = nullptr;
void MySql::openDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        //database.setHostName("customdb");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("root");
        database.setPassword("123456");
    }
    if(database.open()) {
        tablelist = database.tables();
        sqlquery = new QSqlQuery(database);
        qDebug() << "database open ok !";
        qDebug() << "have table num = " << tablelist.count();
        for(int i = 0;i < tablelist.count(); i++) {
            qDebug() << "table " << i + 1 << " : " << tablelist.at(i);
        }
    }
    else {
        qDebug() << "database open fail !";
    }
}

bool MySql::createTableUserInfo(QString tablename)
{
    tablelist = database.tables();
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (userId int PRIMARYKEY UNIQUE, password text, userName text, userImg int, userQ text, userA text, userLabel text, userAge int, userSex int)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
        return true;
    }
    return false;
}

bool MySql::createTableFriend(int id)
{
    tablelist = database.tables();
    QString tablename = "friend" + QString::number(id);
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (friendId INT UNIQUE)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
        return true;
    }
    return false;
}

bool MySql::createTableUserGroup(int id)
{
    tablelist = database.tables();
    QString tablename = "usergroup" + QString::number(id);
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (userId INT UNIQUE)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
        return true;
    }
    return false;
}

bool MySql::createTableGroup(int id)
{
    tablelist = database.tables();
    QString tablename = "group" + QString::number(id);
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (userId INT UNIQUE)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
        return true;
    }
    return false;
}

bool MySql::createTableP2PMsg(int id1, int id2)
{
    tablelist = database.tables();
    QString tablename = "p2pmsg" + QString::number(id1) + "_" + QString::number(id2);
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (TM time, senderId INT, Msg TEXT)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
        return true;
    }
    return false;
}

bool MySql::createTableGroupMsg(int id)
{
    tablelist = database.tables();
    QString tablename = "groupmsg" + QString::number(id);
    if(!tablelist.contains(tablename)) {
        QString createusers = "CREATE TABLE " + tablename + " (TM time, senderId INT, Msg TEXT)";
        if(sqlquery->prepare(createusers)) {
            if(sqlquery->exec()) {
                qDebug() << tablename + " table created !";
                return true;
            }
            else {
                qDebug() << "Error : fail to create table !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << "create command error !";
        }
    }
    else {
        qDebug() << tablename << " already exist !";
//                database_init();
    }
    return false;
}

bool MySql::insertUsersInfo(int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel, int userage, int usersex)
{
    QString insert = "INSERT INTO usersInfo (userId, password, userName, userImg, userQ, userA, userLabel, userAge, userSex) VALUES (";
    insert.append(QString::number(userid));
    insert.append(",");
    insert.append("'" + password + "'");
    insert.append(",");
    insert.append("'" + username + "'");
    insert.append(",");
    insert.append(QString::number(userImg));
    insert.append(",");
    insert.append("'" + userq + "'");
    insert.append(",");
    insert.append("'" + usera + "'");
    insert.append(",");
    insert.append("'" + userlabel + "'");
    insert.append(",");
    insert.append(QString::number(userage));
    insert.append(",");
    insert.append(QString::number(usersex));
    insert.append(")");
    tablelist = database.tables();
    if(!tablelist.contains("friend" + QString::number(userid))) {
        createTableFriend(userid);
        createTableUserGroup(userid);
    }
    return execInsertSql(insert);
}

bool MySql::insertUsersInfo(AllInfo info)
{
    return insertUsersInfo(info.getUserID(),
                    info.getPwd(),
                    info.getNickName(),
                    info.getHeadImgID(),
                    info.getPwdQ(),
                    info.getPwdA(),
                    info.getLabel(),
                    info.getAge(),
                    info.getSex()
                    );
}

void MySql::insertUserFriend(int userid, int friendid)
{
    tablelist = database.tables();
    if(!tablelist.contains("friend" + QString::number(userid))) {
        createTableFriend(userid);
    }
    if(!tablelist.contains("friend" + QString::number(friendid))) {
        createTableFriend(friendid);
    }
    QString insert = "INSERT INTO friend" + QString::number(userid) + " (friendId) VALUES (";
    insert.append(QString::number(friendid));
    insert.append(")");
    execInsertSql(insert);
    insert = "INSERT INTO friend" + QString::number(friendid) + " (friendId) VALUES (";
    insert.append(QString::number(userid));
    insert.append(")");
    execInsertSql(insert);
    createTableP2PMsg(userid, friendid);
    createTableP2PMsg(friendid, userid);
}

void MySql::insertGroupUser(int groupid, QList<int> userid)
{
    QString insert = "INSERT INTO group" + QString::number(groupid) + " (userId) VALUES (";
    QString inserttmp;
    for(auto us : userid) {
        inserttmp = insert;
        inserttmp.append(QString::number(us));
        inserttmp.append(")");
        execInsertSql(inserttmp);
    }
    QString insert1 = "INSERT INTO usergroup";
    QString insert2 = " (userId) VALUES (" + QString::number(groupid) + ")";
    for(auto us : userid) {
        inserttmp = insert1 + QString::number(us) + insert2;
        execInsertSql(inserttmp);
    }
}

void MySql::insertGroupUser(GroupInfo info)
{
    QList<int> meb; meb.clear();
    QHash<int, int> tmp = info.getMemberIdSet();
    for(auto i : tmp) meb.append(i);
    insertGroupUser(info.getGroupid(),
                    meb);
}

void MySql::insertP2PMsg(int senderid, int receiverid, QString tm, QString msg)
{
    QString insert = "INSERT INTO p2pmsg" + QString::number(senderid) + "_" + QString::number(receiverid)
            + " (TM, senderId, Msg) VALUES (";
    insert.append("'" + tm + "'");
    insert.append(",");
    insert.append(QString::number(senderid));
    insert.append(",");
    insert.append("'" + msg + "'");
    insert.append(")");
    execInsertSql(insert);
    insert = "INSERT INTO p2pmsg" + QString::number(receiverid) + "_" + QString::number(senderid)
            + " (TM, senderId, Msg) VALUES (";
    insert.append("'" + tm + "'");
    insert.append(",");
    insert.append(QString::number(senderid));
    insert.append(",");
    insert.append("'" + msg + "'");
    insert.append(")");
    execInsertSql(insert);
}

void MySql::insertP2PMsg(HistoryMessage msg)
{
    insertP2PMsg(msg.getSenderID(),
                 msg.getReceiverID(),
                 msg.getDatetime().toString(),
                 msg.getMessageData()
                 );
}

bool MySql::insertGroupMsg(int groupid, int senderid, QString tm, QString msg)
{
    QString insert = "INSERT INTO groupmsg" + QString::number(groupid)
            + " (TM, senderId, Msg) VALUES (";
    insert.append("'" + tm + "'");
    insert.append(",");
    insert.append(QString::number(senderid));
    insert.append(",");
    insert.append("'" + msg + "'");
    insert.append(")");
    return execInsertSql(insert);
}

bool MySql::insertGroupMsg(HistoryMessage msg)
{
    return insertGroupMsg(msg.getReceiverID(),
                          msg.getSenderID(),
                          msg.getDatetime().toString(),
                          msg.getMessageData()
                          );
}

void MySql::insertGroup(int groupid)
{
    createTableGroup(groupid);
    createTableGroupMsg(groupid);
}

PublicInfo MySql::selectUserPublicInfo(int userid)
{
    QString sqlselect = "SELECT userImg, userId, userName, userSex, userLabel, userAge"
                        " FROM UsersInfo WHERE userID = "
                        + QString::number(userid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    PublicInfo* pubinfo = new PublicInfo;
    while(sqlquery->next()) {
        pubinfo = new PublicInfo(sqlquery->value(0).toInt(),
                                 sqlquery->value(1).toInt(),
                                 sqlquery->value(2).toString(),
                                 sqlquery->value(3).toInt(),
                                 sqlquery->value(4).toString(),
                                 sqlquery->value(5).toInt()
                                 );
    }
    return *pubinfo;
}

QList<PublicInfo> MySql::selectFriendInfo(int userid)
{
    QString sqlselect = "SELECT *"
                        " FROM friend" + QString::number(userid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    QList<PublicInfo> friendinfo; friendinfo.clear();
    while(sqlquery->next()) {
        friendinfo.append(selectUserPublicInfo(sqlquery->value(0).toInt()));
    }
    return friendinfo;
}

QList<int> MySql::selectUserGroupInfo(int userid)
{
    QString sqlselect = "SELECT *"
                        " FROM usergroup" + QString::number(userid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    QList<int> groupinfo; groupinfo.clear();
    while(sqlquery->next()) {
        groupinfo.append(sqlquery->value(0).toInt());
    }
    return groupinfo;
}

QList<PublicInfo> MySql::selectGroupInfo(int groupid)
{
    QString sqlselect = "SELECT *"
                        " FROM group" + QString::number(groupid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    QList<PublicInfo> groupinfo; groupinfo.clear();
    while(sqlquery->next()) {
        groupinfo.append(selectUserPublicInfo(sqlquery->value(0).toInt()));
    }
    return groupinfo;
}

AllInfo MySql::selectUserAllInfo(int userid)
{
    QString sqlselect = "SELECT userImg, userId, userName, userSex, userAge, userq, usera, password, userLabel"
                        " FROM UsersInfo WHERE userID = "
                        + QString::number(userid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    AllInfo* allinfo = new AllInfo;
    while(sqlquery->next()) {
        allinfo = new AllInfo(sqlquery->value(0).toInt(),
                              sqlquery->value(1).toInt(),
                              sqlquery->value(2).toString(),
                              sqlquery->value(3).toInt(),
                              sqlquery->value(4).toInt(),
                              sqlquery->value(5).toString(),
                              sqlquery->value(6).toString(),
                              sqlquery->value(7).toString(),
                              sqlquery->value(8).toString()
                              );
    }
    return *allinfo;
}

QList<HistoryMessage> MySql::selectP2PMsg(int senderid, int receiverid)
{
    QString sqlselect = "SELECT TM, Msg, senderId"
                        " FROM p2pmsg" + QString::number(senderid) + "_" + QString::number(receiverid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    QList<HistoryMessage> msg; msg.clear();
    HistoryMessage* msg1;
    while(sqlquery->next()) {
        int sdid = sqlquery->value(2).toInt();
        msg1 = new HistoryMessage(sqlquery->value(0).toDateTime(),
                           sqlquery->value(1).toString(),
                           sqlquery->value(2).toInt(),
                           (sdid == senderid) ? receiverid : senderid);
        msg.append(*msg1);
    }
    return msg;
}

QList<HistoryMessage> MySql::selectGroupMsg(int groupid)
{
    QString sqlselect = "SELECT TM, Msg, senderId"
                        " FROM groupmsg" + QString::number(groupid);
    if(sqlquery->prepare(sqlselect)) {
        if(sqlquery->exec(sqlselect)) {
            qDebug() << "select ok !";
        }
        else {
            qDebug() << sqlselect;
            qDebug() << "error : select fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlselect;
        qDebug() << "select command error !";
    }
    QList<HistoryMessage> msg; msg.clear();
    HistoryMessage* msg1;
    while(sqlquery->next()) {
        msg1 = new HistoryMessage(sqlquery->value(0).toDateTime(),
                           sqlquery->value(1).toString(),
                           sqlquery->value(2).toInt(),
                           groupid);
        msg.append(*msg1);
    }
    return msg;
}

void MySql::deleteUserInfo(int userid)
{
    QString del = "DELETE FROM usersInfo WHERE userId = " + QString::number(userid);
    if(sqlquery->prepare(del)) {
        if(sqlquery->exec()) {
            qDebug() << "delete data ok !";
        }
        else {
            qDebug() << del;
            qDebug() << "Error : del fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << del;
        qDebug() << "command error !";
    }
}

void MySql::deleteUserFriend(int userid, int friendid)
{
    QString del = "DELETE FROM friend" + QString::number(userid)
            + " WHERE friendId = " + QString::number(friendid);
    if(sqlquery->prepare(del)) {
        if(sqlquery->exec()) {
            qDebug() << "delete data ok !";
        }
        else {
            qDebug() << del;
            qDebug() << "Error : del fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << del;
        qDebug() << "command error !";
    }
}

void MySql::deleteGroupUser(int groupid, QList<int> userid)
{
    QString del1 = "DELETE FROM group" + QString::number(groupid)
            + " WHERE userId = ";
    QString del2 = "DELETE FROM groupmsg" + QString::number(groupid)
            + " WHERE senderId = ";
    QString del3 = "DELETE FROM usergroup";
    QString del4 = " WHERE userId = " + QString::number(groupid);
    QString deltmp1, deltmp2, deltmp3;
    for(auto i : userid) {
        deltmp1 = del1 + QString::number(i);
        deltmp2 = del2 + QString::number(i);
        deltmp3 = del3 + QString::number(i) + del4;
        if(sqlquery->prepare(deltmp1)) {
            if(sqlquery->exec()) {
                qDebug() << "delete data ok !";
            }
            else {
                qDebug() << deltmp1;
                qDebug() << "Error : del fail !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << deltmp1;
            qDebug() << "command error !";
        }
        if(sqlquery->prepare(deltmp2)) {
            if(sqlquery->exec()) {
                qDebug() << "delete data ok !";
            }
            else {
                qDebug() << deltmp2;
                qDebug() << "Error : del fail !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << deltmp2;
            qDebug() << "command error !";
        }
        if(sqlquery->prepare(deltmp3)) {
            if(sqlquery->exec()) {
                qDebug() << "delete data ok !";
            }
            else {
                qDebug() << deltmp3;
                qDebug() << "Error : del fail !" << sqlquery->lastError();
            }
        }
        else {
            qDebug() << deltmp3;
            qDebug() << "command error !";
        }
    }
}

void MySql::dropFriend(int userid, int friendid)
{
    deleteUserFriend(userid, friendid);
    deleteUserFriend(friendid, userid);
    QString tablename = "p2pmsg" + QString::number(userid) + "_" + QString::number(friendid);
    QString drop = "DROP TABLE " + tablename;
    if(sqlquery->prepare(drop)) {
        if(sqlquery->exec()) {
            qDebug() << "drop " + tablename + " table ok !";
        }
        else {
            qDebug() << "Error : drop fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << "drop command error !";
    }
    tablename = "p2pmsg" + QString::number(friendid) + "_" + QString::number(userid);
    drop = "DROP TABLE " + tablename;
    if(sqlquery->prepare(drop)) {
        if(sqlquery->exec()) {
            qDebug() << "drop " + tablename + " table ok !";
        }
        else {
            qDebug() << "Error : drop fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << "drop command error !";
    }
}

void MySql::dropGroup(int groupid)
{
    QList<PublicInfo> groupinfo = selectGroupInfo(groupid);
    QList<int> userid;
    for(auto us : groupinfo) {
        userid.append(us.getUserID());
    }
    deleteGroupUser(groupid, userid);
    QString tablename = "groupmsg" + QString::number(groupid);
    QString drop = "DROP TABLE " + tablename;
    if(sqlquery->prepare(drop)) {
        if(sqlquery->exec()) {
            qDebug() << "drop " + tablename + " table ok !";
        }
        else {
            qDebug() << "Error : drop fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << "drop command error !";
    }
}

bool MySql::updateUsersInfo(int userid, QString password, QString username, int userImg, QString userq, QString usera, QString userlabel, int userage, int usersex)
{
    deleteUserInfo(userid);
    return insertUsersInfo(userid, password, username, userImg, userq, usera, userlabel, userage, usersex);
}

MySql::MySql(QObject *parent) : QObject(parent)
{

}

bool MySql::execInsertSql(QString sqlsentence)
{
    if(sqlquery->prepare(sqlsentence)) {
        if(sqlquery->exec()) {
            qDebug() << "insert data ok !";
            return true;
        }
        else {
            qDebug() << sqlsentence;
            qDebug() << "Error : insert fail !" << sqlquery->lastError();
        }
    }
    else {
        qDebug() << sqlsentence;
        qDebug() << "command error !";
    }
    return false;
}
