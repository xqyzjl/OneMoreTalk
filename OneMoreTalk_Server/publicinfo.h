#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include<QString>

class PublicInfo{
public:
    QString toString();
    PublicInfo(QString info="");
    PublicInfo(int      _headimgID,
               int      _userID,
               QString  _nickname,
               int      _sex=0,
               QString  _label="",
               int      _age=0):
        headimgID   (_headimgID),
        userID      (_userID),
        nickname    (_nickname),
        sex         (_sex),
        label       (_label),
        age         (_age){}
    int getHeadImgID()      const;
    int getUserID()         const;
    QString getNickName()   const;
    int getSex()            const;
    QString getLabel()      const;
    int getAge()            const;

protected:
    int         headimgID;
    int         userID;
    QString     nickname;
    int         sex;
    QString     label;
    int         age;
};
class AllInfo:public PublicInfo{
public:
    QString toString();
    AllInfo(QString info="");
    AllInfo(   int      _headimgID,
               int      _userID,
               QString  _nickname,
               int      _sex=0,
               int      _age=0,
               QString  _passwordFindQuestion="",
               QString  _passwordFindAnswer="",
               QString  _password="",
               QString  _label="你所热爱的，就是你的生活。"){
        headimgID =             _headimgID;
        userID    =             _userID;
        nickname  =             _nickname;
        sex       =             _sex;
        age       =             _age;
        passwordFindQuestion =  _passwordFindQuestion;
        passwordFindAnswer =    _passwordFindAnswer;
        password =              _password;
        label    =              _label;
    }
    QString getPwdQ() const;
    QString getPwdA() const;
    QString getPwd()  const;
private:
    QString passwordFindQuestion;
    QString passwordFindAnswer;
    QString password;
};
#endif // USERINFO_H
