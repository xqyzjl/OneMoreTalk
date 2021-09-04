#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include<QString>

class PublicInfo :public QObject
{
    Q_OBJECT
public:
    explicit PublicInfo(QObject* parent = nullptr);
    QString toString();
    PublicInfo(QString info);
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
        age         (_age){emit sig_PinfoChanged();}
    void set(const PublicInfo & _info);
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


signals:
    void sig_PinfoChanged();
};




class AllInfo:public PublicInfo{
public:
    explicit AllInfo(PublicInfo* parent = nullptr);
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
               QString  _label=""){
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
