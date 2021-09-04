#include "publicinfo.h"
#include<globaldata.h>

const QString SPLIT = GlobalData::SPLIT();

//const QString SPLIT = "123";

PublicInfo::PublicInfo(QString info)
{
    if(info==""){
        headimgID=-1;
        userID=-1;
        nickname="";
        sex=-1;
        age=-1;
        label="";
        return;
    }
    headimgID = info.section(SPLIT,0,0).toInt();
    userID =    info.section(SPLIT,1,1).toInt();
    nickname =  info.section(SPLIT,2,2);
    sex =       info.section(SPLIT,3,3).toInt();
    age =       info.section(SPLIT,4,4).toInt();
    label =     info.section(SPLIT,5,-1);
}

int PublicInfo::getHeadImgID() const
{
    return headimgID;
}

int PublicInfo::getUserID() const
{
    return userID;
}

QString PublicInfo::getNickName() const
{
    return nickname;
}

int PublicInfo::getSex() const
{
    return sex;
}

QString PublicInfo::getLabel() const
{
    return label;
}

int PublicInfo::getAge() const
{
    return age;
}

QString PublicInfo::toString(){
    return  QString::number(headimgID)+SPLIT+
            QString::number(userID)+SPLIT+
            nickname+SPLIT+
            QString::number(sex)+SPLIT+
            QString::number(age)+SPLIT+
            label;
}

AllInfo::AllInfo(QString info)
{
    if(info==""){
        headimgID=-1;
        userID=-1;
        nickname="";
        sex=-1;
        passwordFindQuestion="";
        passwordFindAnswer="";
        password="";
        label="";
        age=0;
        return;
    }
    headimgID =             info.section(SPLIT,0,0).toInt();
    userID =                info.section(SPLIT,1,1).toInt();
    nickname =              info.section(SPLIT,2,2);
    sex =                   info.section(SPLIT,3,3).toInt();
    passwordFindQuestion =  info.section(SPLIT,4,4);
    passwordFindAnswer =    info.section(SPLIT,5,5);
    password =              info.section(SPLIT,6,6);
    age =                   info.section(SPLIT,7,7).toInt();
    label =                 info.section(SPLIT,8,-1);
}

QString AllInfo::getPwdQ() const
{
    return passwordFindQuestion;
}

QString AllInfo::getPwdA() const
{
    return passwordFindAnswer;
}

QString AllInfo::getPwd() const
{
    return password;
}


QString AllInfo::toString(){
    return  QString::number(headimgID)+SPLIT+
            QString::number(userID)+SPLIT+
            nickname+SPLIT+
            QString::number(sex)+SPLIT+
            passwordFindQuestion+SPLIT+
            passwordFindAnswer+SPLIT+
            password+SPLIT+
            QString::number(age)+SPLIT+
            label;
}
