#include "groupinfo.h"

#include <globaldata.h>
const QString SPLIT = GlobalData::SPLIT();

GroupInfo::GroupInfo(){
}

GroupInfo::GroupInfo(QString info){
    auto infoList= info.split(SPLIT);
    int size=infoList[0].toInt();
    groupid=infoList[1].toInt();
    for(int i=2;i<=size+1;i++){
        addMemberId(infoList[i].toInt());
    }
}

GroupInfo::GroupInfo(QList<int> memberList,int _groupid){
    for(auto userID:memberList)
        addMemberId(userID);
    groupid=_groupid;
}

QHash<int,int> GroupInfo::getMemberIdSet() const{
    return memberIdSet;
}

QString GroupInfo::toString() const {
    QString res = QString::number(memberIdSet.size()) + SPLIT;
    res += QString::number(groupid) + SPLIT;
    for(auto memberID:memberIdSet)
        res = res + QString::number(memberID) + SPLIT;
    return res;
}

int GroupInfo::addMemberId(int userID){

    if(memberIdSet.count(userID))
        return 1;
    if(this->size()>=100)
        return 2;
    memberIdSet.insert(userID,userID);
    return 0;
    /*
         * 返回0：正常结束
         * 返回1：群中已存在该ID
         * 返回2：群人数已满
    */
}

int GroupInfo::eraseMemberId(int userID){
    if(!memberIdSet.count(userID))
        return 1;
    memberIdSet.erase(memberIdSet.find(userID));
    return 0;
    /*
         * 返回0：正常结束
         * 返回1：群中不存在该ID
    */
}

int GroupInfo::size() const {
    return memberIdSet.size();
}

int GroupInfo::getGroupid() const{
    return groupid;
}
