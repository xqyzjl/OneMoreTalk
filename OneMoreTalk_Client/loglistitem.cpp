#include "loglistitem.h"
#include<global/globaldata.h>

LogListItem::LogListItem(QWidget *parent) : QWidget(parent)
{
    //初始化
    icon=new QLabel(this);
    name=new QLabel(this);
    msg=new QLabel(this);
    md_msg="";
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    //设置格式
    icon->setFixedSize(40,40);
    //QPixmap icon_pix=QPixmap(":/Resources/icon/("+QString::number(rand()%31+1)+").png");
    //icon->setPixmap(icon_pix.scaled(icon->size()));
    name->setStyleSheet("font-family:'Microsoft YaHei';"
                        "font-size:16px;"
                        "color:grey;");
    msg->setStyleSheet("font-family:'Microsoft YaHei';"
                       "font-size:18px;"
                       "padding:5px;"
                       "border-radius:5px;"
                       "background:rgb(255,255,255);");
    setMsg("This is a message");  //Test
    //布局
    icon->move(5,5);
    msg->move(50,10);
}

LogListItem::LogListItem(int _id)
{
    //初始化
    icon=new QLabel(this);
    name=new QLabel(this);
    msg=new QLabel(this);
    md_msg="";
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    //设置格式
    icon->setFixedSize(40,40);
    name->setStyleSheet("font-family:'Microsoft YaHei';"
                        "font-size:16px;"
                        "color:grey;");
    msg->setStyleSheet("font-family:'Microsoft YaHei';"
                       "font-size:18px;"
                       "padding:5px;"
                       "border-radius:5px;"
                       "background:rgb(255,255,255);");
    setMsg("This is a message");  //Test
    //布局
    name->hide();
    icon->move(5,5);
    msg->move(50,10);
    setID(_id);
    connect(GlobalData::id2PInfo[_id],
            SIGNAL(sig_PinfoChanged()),
            this,
            SLOT(slot_updateMessageInfo()));
}

void LogListItem::setMsg(QString str)
{
    msg->setText(str);
    msg->adjustSize();
}
void LogListItem::setID(int _id)
{
    id = _id;
    if(id<0) return;
    PublicInfo *info = GlobalData::id2PInfo[id];
    QPixmap icon_pix=QPixmap(":/Resources/icon/("+QString::number(info->getHeadImgID())+").png");
    icon->setPixmap(icon_pix.scaled(icon->size()));
    name->setText(info->getNickName());
}
void LogListItem::setMyLog()
{
    icon->move(740-60,icon->y());
    name->move(740-65-name->width(),name->y());
    msg->move(740-65-msg->width(),msg->y());
}
void LogListItem::setGroupLog()
{
    qDebug()<<"setGroupLog()"<<name->text()<<msg->text();
    name->move(50,5); name->show();
    msg->move(50,30);
}

void LogListItem::setMd(QString md_msg)
{
    this->md_msg = md_msg;
    QPixmap pix = QPixmap(":/Resources/md_msg.png");
    msg->setPixmap(pix.scaledToHeight(25));
    msg->adjustSize();
}

void LogListItem::slot_updateMessageInfo()
{
    int icon_id = GlobalData::id2PInfo[id]->getHeadImgID();
    QPixmap icon_pix=QPixmap(":/Resources/icon/("+QString::number(icon_id)+").png");
    icon->setPixmap(icon_pix.scaled(icon->size()));
}

