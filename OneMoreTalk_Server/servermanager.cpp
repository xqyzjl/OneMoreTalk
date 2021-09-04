#include "servermanager.h"

const QString MSG_DATA_SPLIT = GlobalData::MSG_DATA_SPLIT();

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    myTcphand = TcpServer::gethand();
    mySqlhand = MySql::gethand();
    mySqlhand->openDatabase();
    mySqlhand->createTableUserInfo("usersInfo");
    IDMap.clear();

    nextID = mySqlhand->selectMaxId() + 1; //Debug


    qDebug() << "nextid  :  " << nextID;

    connect(myTcphand, &TcpServer::sig_modifyMsg,
            this, &ServerManager::slot_handleMsg);
    connect(myTcphand, &TcpServer::sig_manager_clientLogOut,
            this, &ServerManager::slot_clientLogOut);
}

void ServerManager::slot_handleMsg(QString strmsg, QTcpSocket *socket)
{
    Message msg(strmsg);
    QString msgType = msg.getMessageData().section(GlobalData::MSG_DATA_SPLIT(),1,1);

    QStringList listmsg = msg.deCode();
    qDebug() << "list msg after new decode" << listmsg;
//    int sender = msg.getSenderID();
    int sender = IDMap.key(socket, 0);
    if(sender == 0) {
        sender = msg.getSenderID();
    }
    int receiver = msg.getReceiverID();
    QDateTime dt = msg.getDatetime();

    emit sig_display_activity(
                dt.toString("hh:mm:ss") +
                "  id: " +
                QString::number(sender) +
                ", ip: " +
                socket->peerAddress().toString() +
                " send: " +
                msgType
                );
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
    qDebug() << "In Manager: " << msg << " " << sender << " " << receiver << " " << dt;

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
    sendMessage(socket, backmsg);

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
    if(info.getUserID() == userid && info.getPwd() == password && !IDMap.contains(userid)) backmsgstr = "LOGIN_OK";
    else backmsgstr = "ERROR: LOGIN_ERROR";
    Message backmsg(dt, backmsgstr, 0, sender);
    sendMessage(socket, backmsg);

    // 后续操作
    if(info.getUserID() == userid && info.getPwd() == password) {
        IDMap[userid] = socket;
        qDebug() << "IDMap add" << userid << ' ' << socket;
    }
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
    sendMessage(socket, backmsg);

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
    if(info.getUserID() == sender && answer == info.getPwdA()) {
        backmsgstr = "PASSWORD_FIND_OK";
        if(info.getPwd() == newpassword) backmsgstr = "ERROR: PASSWORD_FIND_SAME_ERROR";
    }
    else backmsgstr = "ERROR: PASSWORD_FIND_ANSWER_ERROR";
    Message backmsg(dt, backmsgstr, 0, sender);
    sendMessage(socket, backmsg);

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
    qDebug() << "IDMap: " <<IDMap;
    if(info.getUserID() == receiverid) { // 私聊
        if(IDMap.contains(receiverid))
            sendMessage(IDMap[receiverid], backmsg);
    }
    else { // 群聊
        QList<PublicInfo> ginfo = mySqlhand->selectGroupInfo(receiverid);
        for(auto us : ginfo) {
            int curid = us.getUserID();
            if(IDMap.contains(curid) && curid != senderid) {
                sendMessage(IDMap[curid], backmsg);
            }
        }
    }

    backmsgstr = "SEND_OK";
    Message backmsg1(dt, backmsgstr, sender, receiver);
    sendMessage(socket, backmsg1);

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
    sendMessage(socket, backmsg);

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
    sendMessage(socket, backmsg);

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
            QString ret = "MESSAGE" + MSG_DATA_SPLIT + QString::number(msghis.getSenderID()) + MSG_DATA_SPLIT + QString::number(msghis.getReceiverID()) + MSG_DATA_SPLIT;
//            QString ret = "FRIEND_HISTORY" + MSG_DATA_SPLIT + QString::number(userID) + MSG_DATA_SPLIT + QString::number(friendID) + MSG_DATA_SPLIT;
//            Message msgg(msghis.getDatetime(), msghis.getMessageData(), msghis.getSenderID(), msghis.getReceiverID());
//          ret.append(msghis.toString());
            ret.append(msghis.toString().section(MSG_DATA_SPLIT,1,1));
            Message ret_msg(dt,ret,0,sender);
            sendMessage(socket, ret_msg);
        }
    }
    else {
        Message ret_msg(dt,"ERROR: FRIEND_HISTORY_ERROR",0,sender);
        sendMessage(socket, ret_msg);
    }
}

void ServerManager::IS_GROUP_HISTORY_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int groupID = msg[1].toInt();
    QList<HistoryMessage> groupHistory = mySqlhand->selectGroupMsg(groupID);
    for (auto msghis : groupHistory) {
        QString ret = "MESSAGE" + MSG_DATA_SPLIT + QString::number(msghis.getSenderID()) + MSG_DATA_SPLIT + QString::number(groupID) + MSG_DATA_SPLIT;
//        QString ret = "GROUP_HISTORY" + MSG_DATA_SPLIT + QString::number(groupID) + MSG_DATA_SPLIT;
//        Message msgg(msghis.getDatetime(), msghis.getMessageData(), msghis.getSenderID(), msghis.getReceiverID());
//        ret.append(msghis.toString());
        ret.append(msghis.toString().section(MSG_DATA_SPLIT,1,1));
        Message ret_msg(dt,ret,0,sender);
        sendMessage(socket, ret_msg);
    }
}

void ServerManager::IS_FRIEND_HISTORY(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_GROUP_HISTORY(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIENDS_INFO_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt();
    QList<PublicInfo> friendIDList = mySqlhand->selectFriendInfo(userID);

    for (auto friendID : friendIDList) {
        qDebug() << friendID.getUserID();
        QString ret = "FRIENDS_INFO" + MSG_DATA_SPLIT;
        ret.append(QString::number(friendID.getUserID()));
        Message ret_msg(dt,ret,0,sender);
        sendMessage(socket, ret_msg);
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
        sendMessage(socket, ret_msg);
    }
}

void ServerManager::IS_FRIENDS_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}
void ServerManager::IS_GROUPS_INFO(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIEND_ADD_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt(), friendID = msg[2].toInt();
    QString ret = "";

    AllInfo info = mySqlhand->selectUserAllInfo(friendID);

    if (info.getUserID() == friendID && userID != friendID) {
        QList<PublicInfo> friendList = mySqlhand->selectFriendInfo(userID);
        bool flag = false;
        for (auto friendInfo : friendList) {
            if (friendInfo.getUserID() == friendID)
                flag = true;
        }
        if (!flag) {
            mySqlhand->insertUserFriend(userID, friendID);
            ret.append("FRIEND_ADD_OK");
        }
        else {
            ret.append("ERROR: FRIEND_ADD_ERROR");
        }
    }
    else {
        ret.append("ERROR: FRIEND_ADD_ERROR");
    }
    Message ret_msg(dt,ret,0,sender);
    sendMessage(socket, ret_msg);
}

void ServerManager::IS_FRIEND_ADD_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_FRIEND_REMOVE_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    int userID = msg[1].toInt(), friendID = msg[2].toInt();
    mySqlhand->dropFriend(userID, friendID);
    Message ret_msg(dt,"FRIEND_REMOVE_OK",0,sender);
    sendMessage(socket, ret_msg);
}

void ServerManager::IS_FRIEND_REMOVE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_GROUP_ADD_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    GroupInfo info(msg[1]);
    int groupID = info.getGroupid();
    QHash<int,int> IDList = info.getMemberIdSet();

    QList<int> newIDList;
    newIDList.clear();
    AllInfo userInfo = mySqlhand->selectUserAllInfo(groupID);
    qDebug() << groupID << ' ' << IDList << ' ' << userInfo.getUserID();
    QString ret = "";
    if (userInfo.getUserID() != groupID) {
        mySqlhand->createTableGroup(groupID);
        mySqlhand->createTableGroupMsg(groupID);
        for (auto userID : IDList) {
            newIDList.append(userID);
        }
        mySqlhand->insertGroupUser(groupID, newIDList);
        ret.append("GROUP_ADD_OK");
    }
    else {
        ret.append("ERROR: GROUP_ADD_ERROR");
    }
    Message ret_msg(dt,ret,0,sender);
    sendMessage(socket, ret_msg);
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
    sendMessage(socket, ret_msg);
}

void ServerManager::IS_GROUPUSER_REMOVE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_USER_INFO_UPDATE_REQUEST(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {
    qDebug() << msg << ' ' << sender << ' ' << receiver << ' ' << dt;
    PublicInfo info(msg[1]);
    int id = info.getUserID();

    AllInfo oldInfo = mySqlhand->selectUserAllInfo(id);

    QString password = oldInfo.getPwd();
    QString username = info.getNickName();
    int img = info.getHeadImgID();
    QString rq = oldInfo.getPwdQ();
    QString ra = oldInfo.getPwdA();
    QString label = info.getLabel();
    int age = info.getAge();
    int sex = info.getSex();
    QString ret = "";
    if (mySqlhand->updateUsersInfo(id, password, username, img, rq, ra, label, age, sex))
        ret.append("USER_INFO_UPDATE_OK");
    else
        ret.append("ERROR: USER_INFO_UPDATE_ERROR");
    Message ret_msg(dt,ret,0,sender);
    sendMessage(socket, ret_msg);
}

void ServerManager::IS_USER_INFO_UPDATE_OK(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::IS_ERROR(QStringList &msg,int sender, int receiver, QDateTime dt, QTcpSocket* socket) {}

void ServerManager::slot_clientLogOut(QTcpSocket* socket) {
    qDebug() << "before log out IDMap" << IDMap;
    int userID = IDMap.key(socket);
    IDMap.remove(userID);
    qDebug() << "manager : client log out " << userID;
    qDebug() << "after log out IDMap" << IDMap;
}

void ServerManager::sendMessage(QTcpSocket *socket, Message msg) {
    qDebug() << "SEND:  " << msg.toString();
    socket->write(msg.toString().toUtf8());
    socket->flush();
    //GlobalData::sleep(1000);
}
