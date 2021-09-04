#ifndef GROUPINFO_H
#define GROUPINFO_H

#include<QHash>
#include<QObject>

class GroupInfo :public QObject
{
    Q_OBJECT
public:
    explicit GroupInfo(QObject* parent = nullptr);
    GroupInfo(QString info);
    GroupInfo(QList<int> memberList,int _groupid);
    QHash<int,int> getMemberIdSet() const;
    QString toString() const;
    void set(const GroupInfo &_info);
    int addMemberId(int userID);
    int eraseMemberId(int userID);
    int size() const;
    int getGroupid() const;
private:
    QHash<int,int> memberIdSet;
    int groupid;

signals:
    void sig_GinfoChanged();
};

#endif // GROUPINFO_H
