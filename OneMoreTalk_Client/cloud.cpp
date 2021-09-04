#include "cloud.h"

const QString MSG_DATA_SPLIT=GlobalData::MSG_DATA_SPLIT();

Cloud* Cloud::myhand=nullptr;

Cloud::Cloud(){}

bool Cloud::set(const QString &IP,int port){
    qDebug()<<"try to connect "<<IP<<":"<<port;
    socket.disconnectFromHost();
    socket.connectToHost(IP, port);
    connect(&socket,    SIGNAL(readyRead()),
            this,       SLOT(slot_fakeread()));
    bool f = socket.waitForConnected(1000);
    return f;
//    connect(this,    SIGNAL(myReadyRead()),
//            this,    SLOT(slot_fakeread()));
}

Cloud* Cloud::gethand(){
    if(myhand==nullptr)
        myhand=new Cloud;
    return myhand;
}

void Cloud::send( int senderID,int receiverID,const QString &msg_data){
    Message msg(QDateTime::currentDateTime(),
                msg_data,
                senderID,
                receiverID);
    qDebug()<<"SEND:  "<<msg.toString();
    socket.write(msg.toString().toUtf8());
    socket.flush();
//    GlobalData::sleep(1000);
}

void Cloud::sendFriendInfoRequest(int userID){
    QString msg_data="SIGNUP_USER_INFO_REQUEST"
            + MSG_DATA_SPLIT
            + QString::number(userID);
    send(GlobalData::MyId,
         CLOUD,
         msg_data);
}

void Cloud::sendFriendHistoryRequest(int userID){
    //    QString msg_data = "_HISTORY_REQUEST"+
    //            MSG_DATA_SPLIT+
    QString msg_data;
    if(userID<0){
        msg_data = "GROUP_HISTORY_REQUEST"+
                MSG_DATA_SPLIT+
                QString::number(userID);
    }
    else{
        msg_data = "FRIEND_HISTORY_REQUEST"+
                MSG_DATA_SPLIT+
                QString::number(GlobalData::MyId)+
                MSG_DATA_SPLIT+
                QString::number(userID);
    }
    send(GlobalData::MyId,CLOUD,msg_data);
}

void Cloud::slot_fakeread(){
    QByteArray buf = socket.readAll();
    QStringList msgs = QString::fromStdString(buf.toStdString()).split(GlobalData::MSG_MSG_SPLIT());
    for(auto msg:msgs)
        read(msg);
}

void Cloud::read(QString str_msg){
    if(str_msg.size()<5) return;
    qDebug()<<"READ:  "<<str_msg;
//    QString strbuf =
    Message msg(str_msg);
    QStringList list_msg=msg.deCode();
    if(list_msg[0].size()==0) return;
    switch(list_msg[0].toInt()){case SIGNUP_QUEST:    {SIG_SIGNUP_QUEST(msg);  break;}
        case SIGNUP_OK:    {SIG_SIGNUP_OK(msg);  break;}
        case LOGIN_QUEST:    {SIG_LOGIN_QUEST(msg);  break;}
        case LOGIN_OK:    {SIG_LOGIN_OK(msg);  break;}
        case PASSWORD_FIND:    {SIG_PASSWORD_FIND(msg);  break;}
        case PASSWORD_PROTECT_ANSWER:    {SIG_PASSWORD_PROTECT_ANSWER(msg);  break;}
        case PASSWORD_PROTECT_QUESTION:    {SIG_PASSWORD_PROTECT_QUESTION(msg);  break;}
        case PASSWORD_FIND_OK:    {SIG_PASSWORD_FIND_OK(msg);  break;}
        case MESSAGE:    {SIG_MESSAGE(msg);  break;}
        case SEND_OK:    {SIG_SEND_OK(msg);  break;}
        case RECEIVE_OK:    {SIG_RECEIVE_OK(msg);  break;}
        case SIGNUP_USER_INFO_REQUEST:    {SIG_SIGNUP_USER_INFO_REQUEST(msg);  break;}
        case GROUP_INFO_REQUEST:    {SIG_GROUP_INFO_REQUEST(msg);  break;}
        case FRIEND_INFO:    {SIG_FRIEND_INFO(msg);  break;}
        case GROUP_INFO:    {SIG_GROUP_INFO(msg);  break;}
        case FRIEND_HISTORY_REQUEST:    {SIG_FRIEND_HISTORY_REQUEST(msg);  break;}
        case GROUP_HISTORY_REQUEST:    {SIG_GROUP_HISTORY_REQUEST(msg);  break;}
        case FRIEND_HISTORY:    {SIG_FRIEND_HISTORY(msg);  break;}
        case GROUP_HISTORY:    {SIG_GROUP_HISTORY(msg);  break;}
        case FRIENDS_INFO_REQUEST:    {SIG_FRIENDS_INFO_REQUEST(msg);  break;}
        case GROUPS_INFO_REQUEST:    {SIG_GROUPS_INFO_REQUEST(msg);  break;}
        case FRIENDS_INFO:    {SIG_FRIENDS_INFO(msg);  break;}
        case GROUPS_INFO:    {SIG_GROUPS_INFO(msg);  break;}
        case FRIEND_ADD_REQUEST:    {SIG_FRIEND_ADD_REQUEST(msg);  break;}
        case FRIEND_ADD_OK:    {SIG_FRIEND_ADD_OK(msg);  break;}
        case FRIEND_REMOVE_REQUEST:    {SIG_FRIEND_REMOVE_REQUEST(msg);  break;}
        case FRIEND_REMOVE_OK:    {SIG_FRIEND_REMOVE_OK(msg);  break;}
        case GROUP_ADD_REQUEST:    {SIG_GROUP_ADD_REQUEST(msg);  break;}
        case GROUP_ADD_OK:    {SIG_GROUP_ADD_OK(msg);  break;}
        case GROUPUSER_REMOVE_REQUEST:    {SIG_GROUPUSER_REMOVE_REQUEST(msg);  break;}
        case GROUPUSER_REMOVE_OK:    {SIG_GROUPUSER_REMOVE_OK(msg);  break;}
        case USER_INFO_UPDATE_REQUEST:    {SIG_USER_INFO_UPDATE_REQUEST(msg);  break;}
        case USER_INFO_UPDATE_OK:    {SIG_USER_INFO_UPDATE_OK(msg);  break;}
        default:    {SIG_ERROR(msg);  break;}
    }
}

void Cloud::SIG_FRIEND_INFO(const Message &msg){
    QString str_userInfo = msg.deCode()[1];
    PublicInfo userInfo(str_userInfo);
    if(!GlobalData::id2PInfo.contains(userInfo.getUserID()))
        GlobalData::id2PInfo[userInfo.getUserID()] = new PublicInfo;
    GlobalData::id2PInfo[userInfo.getUserID()]->set(userInfo);
}

void Cloud::SIG_GROUP_INFO(const Message &msg){
    QString str_groupInfo = msg.deCode()[1];
    GroupInfo groupInfo(str_groupInfo);
    if(!GlobalData::id2GInfo.count(groupInfo.getGroupid()))
        GlobalData::id2GInfo[groupInfo.getGroupid()] = new GroupInfo;
    GlobalData::id2GInfo[groupInfo.getGroupid()]->set(groupInfo);
}
