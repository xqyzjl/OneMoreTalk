#include "globaldata.h"

QString GlobalData::SPLIT() {
    QString ans={(char)0xff};
    return ans;
}

QString GlobalData::MSG_SPLIT() {
    QString ans={(char)0xfe};
    return ans;
}

QString GlobalData::MSG_DATA_SPLIT() {
    QString ans={(char)0xfd};
    return ans;
}

QMap<QString,QString> GlobalData::__state2int;
QMap<int,QString> GlobalData::__int2state;

QString GlobalData::state2int(QString state){
    if(__state2int.empty()){
        __state2int["SIGNUP_QUEST"]=QString::number(SIGNUP_QUEST);
        __state2int["SIGNUP_OK"]=QString::number(SIGNUP_OK);
        __state2int["LOGIN_QUEST"]=QString::number(LOGIN_QUEST);
        __state2int["LOGIN_OK"]=QString::number(LOGIN_OK);
        __state2int["PASSWORD_FIND"]=QString::number(PASSWORD_FIND);
        __state2int["PASSWORD_PROTECT_ANSWER"]=QString::number(PASSWORD_PROTECT_ANSWER);
        __state2int["PASSWORD_PROTECT_QUESTION"]=QString::number(PASSWORD_PROTECT_QUESTION);
        __state2int["PASSWORD_FIND_OK"]=QString::number(PASSWORD_FIND_OK);
        __state2int["MESSAGE"]=QString::number(MESSAGE);
        __state2int["SEND_OK"]=QString::number(SEND_OK);
        __state2int["RECEIVE_OK"]=QString::number(RECEIVE_OK);
        __state2int["SIGNUP_USER_INFO_REQUEST"]=QString::number(SIGNUP_USER_INFO_REQUEST);
        __state2int["GROUP_INFO_REQUEST"]=QString::number(GROUP_INFO_REQUEST);
        __state2int["FRIEND_INFO"]=QString::number(FRIEND_INFO);
        __state2int["GROUP_INFO"]=QString::number(GROUP_INFO);
        __state2int["FRIEND_HISTORY_REQUEST"]=QString::number(FRIEND_HISTORY_REQUEST);
        __state2int["GROUP_HISTORY_REQUEST"]=QString::number(GROUP_HISTORY_REQUEST);
        __state2int["FRIEND_HISTORY"]=QString::number(FRIEND_HISTORY);
        __state2int["GROUP_HISTORY"]=QString::number(GROUP_HISTORY);
        __state2int["FRIENDS_INFO_REQUEST"]=QString::number(FRIENDS_INFO_REQUEST);
        __state2int["GROUPS_INFO_REQUEST"]=QString::number(GROUPS_INFO_REQUEST);
        __state2int["FRIENDS_INFO"]=QString::number(FRIENDS_INFO);
        __state2int["GROUPS_INFO"]=QString::number(GROUPS_INFO);
        __state2int["FRIEND_ADD_REQUEST"]=QString::number(FRIEND_ADD_REQUEST);
        __state2int["FRIEND_ADD_OK"]=QString::number(FRIEND_ADD_OK);
        __state2int["FRIEND_REMOVE_REQUEST"]=QString::number(FRIEND_REMOVE_REQUEST);
        __state2int["FRIEND_REMOVE_OK"]=QString::number(FRIEND_REMOVE_OK);
        __state2int["GROUP_ADD_REQUEST"]=QString::number(GROUP_ADD_REQUEST);
        __state2int["GROUP_ADD_OK"]=QString::number(GROUP_ADD_OK);
        __state2int["GROUPUSER_REMOVE_REQUEST"]=QString::number(GROUPUSER_REMOVE_REQUEST);
        __state2int["GROUPUSER_REMOVE_OK"]=QString::number(GROUPUSER_REMOVE_OK);
        __state2int["USER_INFO_UPDATE_REQUEST"]=QString::number(USER_INFO_UPDATE_REQUEST);
        __state2int["USER_INFO_UPDATE_OK"]=QString::number(USER_INFO_UPDATE_OK);
        __state2int["ERROR"]=QString::number(ERROR);
        for(auto p=__state2int.begin();p!=__state2int.end();++p){
            __int2state[p.value().toInt()]=p.key();
        }
    }
    if(!__state2int.count(state)) return "0";
    return __state2int[state];
}
