#include "servermanager.h"

const QString MSG_DATA_SPLIT = GlobalData::MSG_DATA_SPLIT();

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    myTcphand = TcpServer::gethand();
    mySqlhand = MySql::gethand();
    mySqlhand->openDatabase();
    mySqlhand->createTableUserInfo("usersInfo");
    IDMap.clear();
    connect(myTcphand, &TcpServer::sig_modifyMsg,
            this, &ServerManager::slot_handleMsg);
    connect(myTcphand, &TcpServer::sig_manager_clientLogOut,
            this, &ServerManager::slot_clientLogOut);
}

void ServerManager::slot_handleMsg(QString strmsg, QTcpSocket *socket)
{
    Message msg(strmsg);
    QStringList listmsg = msg.deCode();
    int sender = msg.getSenderID();
    int receiver = msg.getReceiverID();
    QDateTime dt = msg.getDatetime();
    switch(listmsg[0].toInt()) {
    case SIGNUP_QUEST:{
        IS_SIGNUP_QUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case SIGNUP_OK:{
        IS_SIGNUP_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case LOGIN_QUEST:{
        IS_LOGIN_QUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case LOGIN_OK:{
        IS_LOGIN_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case PASSWORD_FIND:{
        IS_PASSWORD_FIND(listmsg, sender, receiver, dt, socket);
        break;
    }
    case PASSWORD_PROTECT_ANSWER:{
        IS_PASSWORD_PROTECT_ANSWER(listmsg, sender, receiver, dt, socket);
        break;
    }
    case PASSWORD_PROTECT_QUESTION:{
        IS_PASSWORD_PROTECT_QUESTION(listmsg, sender, receiver, dt, socket);
        break;
    }
    case PASSWORD_FIND_OK:{
        IS_PASSWORD_FIND_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case MESSAGE:{
        IS_MESSAGE(listmsg, sender, receiver, dt, socket);
        break;
    }
    case SEND_OK:{
        IS_SEND_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case RECEIVE_OK:{
        IS_RECEIVE_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case SIGNUP_USER_INFO_REQUEST:{
        IS_SIGNUP_USER_INFO_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_INFO_REQUEST:{
        IS_GROUP_INFO_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_INFO:{
        IS_FRIEND_INFO(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_INFO:{
        IS_GROUP_INFO(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_HISTORY_REQUEST:{
        IS_FRIEND_HISTORY_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_HISTORY_REQUEST:{
        IS_GROUP_HISTORY_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_HISTORY:{
        IS_FRIEND_HISTORY(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_HISTORY:{
        IS_GROUP_HISTORY(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIENDS_INFO_REQUEST:{
        IS_FRIENDS_INFO_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUPS_INFO_REQUEST:{
        IS_GROUPS_INFO_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIENDS_INFO:{
        IS_FRIENDS_INFO(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUPS_INFO:{
        IS_GROUPS_INFO(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_ADD_REQUEST:{
        IS_FRIEND_ADD_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_ADD_OK:{
        IS_FRIEND_ADD_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_REMOVE_REQUEST:{
        IS_FRIEND_REMOVE_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case FRIEND_REMOVE_OK:{
        IS_FRIEND_REMOVE_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_ADD_REQUEST:{
        IS_GROUP_ADD_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUP_ADD_OK:{
        IS_GROUP_ADD_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUPUSER_REMOVE_REQUEST:{
        IS_GROUPUSER_REMOVE_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case GROUPUSER_REMOVE_OK:{
        IS_GROUPUSER_REMOVE_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case USER_INFO_UPDATE_REQUEST:{
        IS_USER_INFO_UPDATE_REQUEST(listmsg, sender, receiver, dt, socket);
        break;
    }
    case USER_INFO_UPDATE_OK:{
        IS_USER_INFO_UPDATE_OK(listmsg, sender, receiver, dt, socket);
        break;
    }
    case ERROR:{
        IS_ERROR(listmsg, sender, receiver, dt, socket);
        break;
    }
    default:
        break;
    }

}
void ServerManager::IS_SIGNUP_QUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    QString nickname = msg[1];
    QString password = msg[2];
    QString question = msg[3];
    QString answer = msg[4];

    // 处理信息
    AllInfo info(0, nextID, nickname, 0, 0, question, answer, password);
    mySqlhand->insertUsersInfo(info);
    mySqlhand->createTableFriend(nextID);
    mySqlhand->createTableUserGroup(nextID);

    // 返回信息
    QString backmsgstr;
    backmsgstr = "SIGNUP_OK" + MSG_DATA_SPLIT + QString::number(nextID);
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作
    nextID++;
}
void ServerManager::IS_SIGNUP_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_LOGIN_QUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    int userid = msg[1].toInt();
    QString password = msg[2];

    // 处理信息
    AllInfo info = mySqlhand->selectUserAllInfo(userid);

    // 返回信息
    QString backmsgstr;
    if(info.getUserID() == userid && info.getPwd() == password) backmsgstr = "LOGIN_OK";
    else backmsgstr = "ERROR: LOGIN_ERROR";
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作
    if(info.getUserID() == userid) IDMap[userid] = socket;
}
void ServerManager::IS_LOGIN_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_PASSWORD_FIND(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    int userid = msg[1].toInt();

    // 处理信息
    AllInfo info = mySqlhand->selectUserAllInfo(userid);

    // 返回信息
    QString backmsgstr;
    if(info.getUserID() == userid) backmsgstr = "PASSWORD_PROTECT_QUESTION" + MSG_DATA_SPLIT + info.getPwdQ();
    else backmsgstr = "ERROR: PASSWORD_FIND_USERID_ERROR";
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作

}
void ServerManager::IS_PASSWORD_PROTECT_ANSWER(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    QString answer = msg[1];
    QString newpassword = msg[2];

    // 处理信息
    AllInfo info = mySqlhand->selectUserAllInfo(sender);
    AllInfo newinfo(info.getHeadImgID(),
                    info.getUserID(),
                    info.getNickName(),
                    info.getSex(),
                    info.getAge(),
                    info.getPwdQ(),
                    info.getPwdA(),
                    newpassword,
                    info.getLabel());
    if(sender == info.getUserID() && answer == info.getPwdA()) {
        mySqlhand->deleteUserInfo(sender);
        mySqlhand->insertUsersInfo(newinfo);
    }

    // 返回信息
    QString backmsgstr;
    if(info.getUserID() == sender && answer == info.getPwdA()) backmsgstr = "PASSWORD_FIND_OK";
    else if(info.getPwd() == newpassword) backmsgstr = "ERROR: PASSWORD_FIND_SAME_ERROR";
    else backmsgstr = "ERROR: PASSWORD_FIND_ANSWER_ERROR";
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作

}
void ServerManager::IS_PASSWORD_PROTECT_QUESTION(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_PASSWORD_FIND_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_MESSAGE(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    int senderid = msg[1].toInt();
    int receiverid = msg[2].toInt();
    QString message = msg[3];

    // 处理信息
    QList<PublicInfo> finfo = mySqlhand->selectFriendInfo(senderid);
    bool flag = false;
    for(auto fusr : finfo) {
        if(fusr.getUserID() == receiverid) {
            flag = true;
            break;
        }
    }
    AllInfo info = mySqlhand->selectUserAllInfo(receiverid);
    if(info.getUserID() == receiverid) { // 私聊
        if(flag)
            mySqlhand->insertP2PMsg(senderid, receiverid, dt.toString(), message);
    }
    else { // 群聊
        mySqlhand->insertGroupMsg(receiverid, senderid, dt.toString(), message);
        flag = true;
    }

    // 返回信息
    QString backmsgstr;
    if(!flag) {
        backmsgstr = "ERROR: SEND_ERROR";
        Message backmsg(dt, backmsgstr, 0, sender);
        return;
    }
    backmsgstr = "MESSAGE"
                + MSG_DATA_SPLIT + QString::number(senderid)
                + MSG_DATA_SPLIT + QString::number(receiverid)
                + MSG_DATA_SPLIT + message;
    Message backmsg(dt, backmsgstr, sender, receiver);
    if(info.getUserID() == receiverid) { // 私聊
        if(IDMap.contains(receiverid))
            IDMap[receiverid]->write(backmsg.toString().toUtf8());
    }
    else { // 群聊
        QList<PublicInfo> ginfo = mySqlhand->selectGroupInfo(receiverid);
        for(auto us : ginfo) {
            int curid = us.getUserID();
            if(IDMap.contains(curid) && curid != senderid) {
                IDMap[curid]->write(backmsg.toString().toUtf8());
            }
        }
    }

    backmsgstr = "SEND_OK";
    Message backmsg1(dt, backmsgstr, sender, receiver);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作

}
void ServerManager::IS_SEND_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_RECEIVE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {

}
void ServerManager::IS_SIGNUP_USER_INFO_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    int userid = msg[1].toInt();

    // 处理信息
    PublicInfo info = mySqlhand->selectUserPublicInfo(userid);

    // 返回信息
    QString backmsgstr;
    if(info.getUserID() == userid) {
        backmsgstr = "FRIEND_INFO" + MSG_DATA_SPLIT + info.toString();
    }
    else {
        backmsgstr = "ERROR: FRIEND_INFO_ERROR";
    }
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作

}
void ServerManager::IS_GROUP_INFO_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    // 调试打印
    qDebug() << msg << " " << sender << " " << receiver << " " << dt;

    // 解析信息
    int groupid = msg[1].toInt();

    // 处理信息
    QList<PublicInfo> ginfo = mySqlhand->selectGroupInfo(groupid);

    // 返回信息
    QString backmsgstr;
    QList<int> guser; guser.clear();
    for(auto us : ginfo) guser.append(us.getUserID());
    GroupInfo groupinfo(guser, groupid);
    backmsgstr = groupinfo.toString();
    Message backmsg(dt, backmsgstr, 0, sender);
    socket->write(backmsg.toString().toUtf8());

    // 后续操作

}
void ServerManager::IS_FRIEND_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_GROUP_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_FRIEND_HISTORY_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt(), friendID = msg[2].toInt();

    AllInfo friendInfo = mySqlhand->selectUserAllInfo(friendID);
    QList<PublicInfo> friendList = mySqlhand->selectFriendInfo(userID);
    bool friendOccur = false;
    for (auto ifriend : friendList) {
        if (ifriend.getUserID() == friendID)
            friendOccur = true;
    }
    if (friendInfo.getUserID() == friendID && friendOccur == true) {
        QList<HistoryMessage> friendHistory = mySqlhand->selectP2PMsg(userID,friendID);
        for (auto msghis : friendHistory) {
            QString ret = "FRIEND_HISTORY" + MSG_DATA_SPLIT + QString::number(userID) + MSG_DATA_SPLIT + QString::number(friendID) + MSG_DATA_SPLIT;
            ret.append(msghis.toString());
            Message ret_msg(dt,ret,0,sender);
            socket->write(ret_msg.toString().toUtf8());
        }
    }
    else {
        Message ret_msg(dt,"ERROR: FRIEND_HISTORY_ERROR",0,sender);
        socket->write(ret_msg.toString().toUtf8());
    }
}

void ServerManager::IS_GROUP_HISTORY_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int groupID = msg[1].toInt();
    QList<HistoryMessage> groupHistory = mySqlhand->selectGroupMsg(groupID);
    for (auto msghis : groupHistory) {
        QString ret = "GROUP_HISTORY" + MSG_DATA_SPLIT + QString::number(groupID) + MSG_DATA_SPLIT;
        ret.append(msghis.toString());
        Message ret_msg(dt,ret,0,sender);
        socket->write(ret_msg.toString().toUtf8());
    }
}

void ServerManager::IS_FRIEND_HISTORY(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_GROUP_HISTORY(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIENDS_INFO_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt();
    QList<PublicInfo> friendIDList = mySqlhand->selectFriendInfo(userID);

    for (auto friendID : friendIDList) {
        QString ret = "FRIENDS_INFO" + MSG_DATA_SPLIT;
        ret.append(QString::number(friendID.getUserID()));
        Message ret_msg(dt,ret,0,sender);
        socket->write(ret_msg.toString().toUtf8());
    }
}

void ServerManager::IS_GROUPS_INFO_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt();
    QList<int> groupIDList = mySqlhand->selectUserGroupInfo(userID);

    for (auto groupID : groupIDList) {
        QString ret = "GROUPS_INFO" + MSG_DATA_SPLIT;
        ret.append(QString::number(groupID));
        Message ret_msg(dt,ret,0,sender);
        socket->write(ret_msg.toString().toUtf8());
    }
}

void ServerManager::IS_FRIENDS_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_GROUPS_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIEND_ADD_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt(), friendID = msg[2].toInt();
    QString ret = "";

    AllInfo info = mySqlhand->selectUserAllInfo(friendID);
    if (info.getUserID() == friendID) {
        mySqlhand->insertUserFriend(userID, friendID);
        ret.append("FRIEND_ADD_OK");
    }
    else {
        ret.append("ERROR: FRIEND_ADD_ERROR");
    }
    Message ret_msg(dt,ret,0,sender);
    socket->write(ret_msg.toString().toUtf8());
}

void ServerManager::IS_FRIEND_ADD_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIEND_REMOVE_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt(), friendID = msg[2].toInt();
    mySqlhand->deleteUserFriend(userID, friendID);
    Message ret_msg(dt,"FRIEND_REMOVE_OK",0,sender);
    socket->write(ret_msg.toString().toUtf8());
}

void ServerManager::IS_FRIEND_REMOVE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_GROUP_ADD_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    GroupInfo info(msg[1]);
    int groupID = info.getGroupid();
    AllInfo userInfo = mySqlhand->selectUserAllInfo(groupID);

    QString ret = "";
    if (userInfo.getUserID() == groupID) {
        mySqlhand->createTableGroup(info.getGroupid());
        ret.append("GROUP_ADD_OK");
    }
    else {
        ret.append("ERROR: GROUP_ADD_ERROR");
    }
    Message ret_msg(dt,ret,0,sender);
    socket->write(ret_msg.toString().toUtf8());
}

void ServerManager::IS_GROUP_ADD_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_GROUPUSER_REMOVE_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int groupID = msg[1].toInt();
    QList<int> userList;
    userList.append(msg[2].toInt());
    mySqlhand->deleteGroupUser(groupID,userList);
    QString ret = "GROUPUSER_REMOVE_OK";
    Message ret_msg(dt,ret,0,sender);
    socket->write(ret_msg.toString().toUtf8());
}

void ServerManager::IS_GROUPUSER_REMOVE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_USER_INFO_UPDATE_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    AllInfo info(msg[1]);
    int id = info.getUserID();
    QString password = info.getPwd();
    QString username = info.getNickName();
    int img = info.getHeadImgID();
    QString rq = info.getPwdQ();
    QString ra = info.getPwdA();
    QString label = info.getLabel();
    int age = info.getAge();
    int sex = info.getSex();
    QString ret = "";
    if (mySqlhand->updateUsersInfo(id,password,username,img,rq,ra,label,age,sex))
        ret.append("USER_INFO_UPDATE_OK");
    else
        ret.append("ERROR: USER_INFO_UPDATE_ERROR");
    Message ret_msg(dt,ret,0,sender);
    socket->write(ret_msg.toString().toUtf8());
}

void ServerManager::IS_USER_INFO_UPDATE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_ERROR(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::slot_clientLogOut(QTcpSocket* socket) {
    int userID = IDMap.key(socket);
    IDMap.remove(userID);
    qDebug() << "manager : client log out " << userID;
}
