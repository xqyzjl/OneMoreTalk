#include "friendlistitem.h"
#include "global/globaldata.h"

FriendListItem::FriendListItem(QWidget *parent) : QWidget(parent)
{
    //初始化
    icon=new QLabel(this);
    name=new QLabel(this);
    sign=new QLabel(this);
    dot=new QLabel(this);
    //设置格式
    icon->setFixedSize(50,50);
    name->setStyleSheet("font-family:'Microsoft YaHei';font-size:20px");
    sign->setStyleSheet("color:grey;font-family:'Microsoft YaHei';font-size:16px;");
    dot->setStyleSheet("color:red;font-family:'Microsoft YaHei';");
    dot->setText("[New]"); dot->hide();
//    setID(rand()%100+1001);    //Test
    //布局
    icon->move(10,10);
    name->move(70,15);
    sign->move(70,40);
    dot->move(350,10);
}

void FriendListItem::setID(int id)
{
    this->id = id;
    //向服务器询问该ID是用户还是群
    if(id>0)    //是用户
    {
        connect((GlobalData::id2PInfo)[id],SIGNAL(sig_PinfoChanged()),
                this,SLOT(slot_PinfoChanged()));
        QPixmap icon_pix; icon_pix.load(":/Resources/icon/("+QString::number(rand()%31+1)+").png");
        icon_pix = icon_pix.scaled(icon->size());
        icon->setPixmap(icon_pix);
        name->setText("User"+QString::number(id)); name->adjustSize();
        sign->setText("This is [User]"+QString::number(id)); sign->adjustSize();
    }
    else
    {
        QPixmap icon_pix; icon_pix.load(":/Resources/icon/group.png");
        icon_pix = icon_pix.scaled(icon->size());
        icon->setPixmap(icon_pix);
        name->setText("[Group]"+QString::number(-id)); name->adjustSize();
        sign->setText("Have fun with friends!"); sign->adjustSize();
    }
}



void FriendListItem::setDot(bool f)
{
    if(f) dot->show(); else dot->hide();
}
void FriendListItem::setSign(QString str)
{
    sign->setText(str);
}

bool flag=false;

void FriendListItem::slot_PinfoChanged(){
//    if(!flag) flag=1;
//    else return;
    PublicInfo *userinfo = GlobalData::id2PInfo[this->id];
    QPixmap icon_pix;
    icon_pix.load(":/Resources/icon/("+QString::number(userinfo->getHeadImgID())+").png");
    icon_pix = icon_pix.scaled(icon->size());
    icon->setPixmap(icon_pix);
    name->setText(userinfo->getNickName()); name->adjustSize();
    sign->setText(userinfo->getLabel()); sign->adjustSize();
}
