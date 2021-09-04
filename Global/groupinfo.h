#ifndef GROUPINFO_H
#define GROUPINFO_H

#include<QHash>

class GroupInfo
{
public:
    GroupInfo();
    GroupInfo(QString info);
    GroupInfo(QList<int> memberList,int _groupid);
    QHash<int,int> getMemberIdSet() const;
    QString toString() const;
    int addMemberId(int userID);
    int eraseMemberId(int userID);
    int size() const;
    int getGroupid() const;
private:
    QHash<int,int> memberIdSet;
    int groupid;
};

#endif // GROUPINFO_H
