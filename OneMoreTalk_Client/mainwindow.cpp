#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <global/globaldata.h>
#include<cloud.h>


QString MSG_DATA_SPLIT = GlobalData::MSG_DATA_SPLIT();
QString MSG_SPLIT = GlobalData::MSG_SPLIT();

int MainWindow::myID = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 请求历史记录槽
    connect(Cloud::gethand(),
            SIGNAL(SIG_FRIEND_HISTORY(const Message &)),
            this,
            SLOT(slot_getHistoryMessage(const Message &))
    );
    //请求好友曹
    connect(Cloud::gethand(),
            SIGNAL(SIG_FRIEND_ADD_OK(const Message &)),
            this,
            SLOT(slot_addfriend(const Message &)));
    connect(Cloud::gethand(),
            SIGNAL(SIG_GROUP_ADD_OK(const Message &)),
            this,
            SLOT(slot_addfriend(const Message &)));
    //加载个人信息
    myID = GlobalData::MyId;
    curID = 0;
    GlobalData::id2PInfo[myID] = new PublicInfo();
    connect(GlobalData::id2PInfo[myID],
            SIGNAL(sig_PinfoChanged()),
            this,
            SLOT(slot_MyInfoUpdate())
            );
    Cloud::gethand()->sendFriendInfoRequest(myID);
    //加载好友列表
    connect(Cloud::gethand(),
            SIGNAL(SIG_FRIENDS_INFO(const Message&)),
            this,
            SLOT(slot_loadFriendList(const Message&)));
    connect(Cloud::gethand(),
            SIGNAL(SIG_GROUPS_INFO(const Message&)),
            this,
            SLOT(slot_loadFriendList(const Message&)));
    QString str_msg="FRIENDS_INFO_REQUEST"+
            MSG_DATA_SPLIT+
            QString::number(myID);  //好友列表请求
    Cloud::gethand()->send(myID,CLOUD,str_msg);
    str_msg="GROUPS_INFO_REQUEST"+
            MSG_DATA_SPLIT+
            QString::number(myID);  //群聊列表请求
    Cloud::gethand()->send(myID,CLOUD,str_msg);
    //连接消息模块
    connect(Cloud::gethand(),
            SIGNAL(SIG_MESSAGE(const Message &)),
            this,
            SLOT(slot_getMessage(const Message &)));
    //加载按钮图标
    QPixmap func_icon=QPixmap(":/Resources/md_icon.png");
    ui->pushButton_func1->setIcon((QIcon)func_icon);
    //其他
    hideRight();
    iw=new InfoWindow(myID);
    mdw=new MDWindow(); mdw->mw=this;
    msg_box.setWindowTitle("Error!");
    connect(mdw,SIGNAL(sig_sendMarkdown(QString)),this,SLOT(slot_sendMarkdown(QString)));
    connect(this,SIGNAL(sig_getMarkdown(QString)),mdw,SLOT(slot_getMarkdown(QString)));
    connect(Cloud::gethand(),SIGNAL(SIG_ERROR(const Message&)),
            this,SLOT(slot_Error(const Message&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//隐藏右侧控件
void MainWindow::hideRight()
{
    ui->pushButton_friendName->hide();
    ui->label_friendID->hide();
    ui->line->hide();
    ui->listWidget_log->hide();
    ui->pushButton_func1->hide();
    ui->label_length->hide();
    ui->lineEdit_send->hide();
    ui->pushButton_send->hide();
}
//显示右侧控件
void MainWindow::showRight()
{
    ui->pushButton_friendName->show();
    ui->label_friendID->show();
    ui->line->show();
    ui->listWidget_log->show();
    ui->pushButton_func1->show();
    ui->label_length->show();
    ui->lineEdit_send->show();
    ui->pushButton_send->show();
}

void MainWindow::on_listWidget_friend_itemClicked(QListWidgetItem *item)    //切换聊天栏
{
    showRight();
    FriendListItem *fri_item = (FriendListItem*)ui->listWidget_friend->itemWidget(item);
    if(fri_item->id>0) Cloud::gethand()->sendFriendInfoRequest(fri_item->id);
    curID = fri_item->id;
    if(!had_load_message[fri_item->id]){
        Cloud::gethand()->sendFriendHistoryRequest(fri_item->id);
        QListWidget *log_list = all_log_list[friend_pos[fri_item->id]];
        while(log_list->count()>0) delete log_list->item(0);
        had_load_message[fri_item->id] = 1;
        fri_item->setDot(false);
    }
    ui->pushButton_friendName->setText(fri_item->getName());
    ui->pushButton_friendName->adjustSize();
    ui->label_friendID->setText("ID: "+QString::number(curID));
    ui->listWidget_log->hide();
    ui->listWidget_log = all_log_list[fri_item->pos];
    ui->listWidget_log->scrollToBottom();
    ui->listWidget_log->show();
    //qDebug()<<all_log_list[fri_item->pos]->count()<<fri_item->pos;
    fri_item->setDot(false);
}

void MainWindow::slot_addfriend(const Message &msg)
{
    if(ui->lineEdit_add->text().left(7)=="[Group]")
        addFriendItem(-ui->lineEdit_add->text().mid(7).toInt());
    else
    {
        int id = ui->lineEdit_add->text().toInt();
        addFriendItem(ui->lineEdit_add->text().toInt());
        QString str_msg="MESSAGE"+
                MSG_DATA_SPLIT+
                QString::number(myID)+
                MSG_DATA_SPLIT+
                QString::number(id)+
                MSG_DATA_SPLIT+
                "[有一个人前来聊天...]";
        Cloud::gethand()->send(myID,id,str_msg);
        LogListItem *log_item=new LogListItem(myID);
        log_item->setMsg("[有一个人前来聊天...]");
        log_item->setID(myID);
        addLogItem(ui->listWidget_log,myID,log_item);
        ui->lineEdit_send->setText("");
        ui->listWidget_log->scrollToBottom();
    }
    ui->lineEdit_add->clear();
    ui->lineEdit_add->setEnabled(true);
}

void MainWindow::on_pushButton_send_clicked()
{
    if(ui->lineEdit_send->text()=="") return;
    //发送消息
    QString str_msg="MESSAGE"+
            MSG_DATA_SPLIT+
            QString::number(myID)+
            MSG_DATA_SPLIT+
            ui->label_friendID->text().mid(4)+
            MSG_DATA_SPLIT+
            ui->lineEdit_send->text();
    Cloud::gethand()->send(myID,
                           curID,
                           str_msg);
    //创建消息
    LogListItem *log_item=new LogListItem(myID);
    log_item->setMsg(ui->lineEdit_send->text());
    log_item->setID(myID);
    if(curID<0) log_item->setGroupLog();
    addLogItem(ui->listWidget_log,myID,log_item);
    ui->lineEdit_send->setText("");
    ui->listWidget_log->scrollToBottom();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
        on_pushButton_send_clicked();
}

void MainWindow::on_lineEdit_send_textChanged(const QString &arg1)
{
    int len=arg1.length();
    if(len>=30) ui->lineEdit_send->setText(ui->lineEdit_send->text().left(30));
    ui->label_length->setText(QString::number(ui->lineEdit_send->text().length())+"/30");
}

void MainWindow::on_pushButton_add_clicked()
{
    if(ui->lineEdit_add->text().left(7)=="[Group]")
    {
        int id=ui->lineEdit_add->text().mid(7).toInt();
        if(ui->lineEdit_add->text().mid(7)!=QString::number(id))
        {
            msg_box.setText("Invalid GroupID!");
            msg_box.exec();
            return;
        }
        //向服务器申请创建群聊
        QList<int> member; member.append(myID);
        GroupInfo info(member,-id);
        QString str_msg="GROUP_ADD_REQUEST"
                        +GlobalData::MSG_DATA_SPLIT()
                        +info.toString();
        Cloud::gethand()->send(myID,CLOUD,str_msg);
//        FriendListItem *fri_item = addFriendItem(id);
//        fri_item->setDot(true);
//        ui->listWidget_log->scrollToBottom();
    }
    else
    {
        int id=ui->lineEdit_add->text().toUInt();
        if(ui->lineEdit_add->text()!=QString::number(id))
        {
            msg_box.setText("Invalid UserID!");
            msg_box.exec();
            return;
        }
        //[与服务器通讯确定ID是否存在，返回对应信息]
        QString str_msg="FRIEND_ADD_REQUEST"+
                MSG_DATA_SPLIT+
                QString::number(myID)+
                MSG_DATA_SPLIT+
                ui->lineEdit_add->text();
        Cloud::gethand()->send(myID,CLOUD,str_msg);
//        FriendListItem *fri_item = addFriendItem(id);
//        fri_item->setDot(true);
//        ui->listWidget_log->scrollToBottom();
    }

    ui->lineEdit_add->setEnabled(false);
}

FriendListItem* MainWindow::addFriendItem(int ID)
{
    if(friend_pos.contains(ID))
        return (FriendListItem*)ui->listWidget_friend->
                itemWidget(ui->listWidget_friend->item(friend_pos[ID]));
    if(ID>0 && !GlobalData::id2PInfo.count(ID))
        GlobalData::id2PInfo[ID] = new PublicInfo;
    if(ID<0 && !GlobalData::id2GInfo.count(ID))
        GlobalData::id2GInfo[ID] = new GroupInfo;

    QListWidget *friend_list = ui->listWidget_friend;
    FriendListItem *friend_item = new FriendListItem();
    friend_pos[ID] = friend_list->count();
    friend_item->pos = friend_list->count();
    friend_item->setID(ID);  //Test
    QListWidgetItem *newItem = new QListWidgetItem();
    friend_list->addItem(newItem);
    friend_list->setItemWidget(newItem,friend_item);

    QListWidget *log_list=new QListWidget();
    log_list->setParent(this);
    log_list->setGeometry(ui->listWidget_log->geometry());
    log_list->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    if(ID>0) log_list->setStyleSheet("QListWidget{background:rgb(240,240,240);border:none;}"
                                     "QListWidget::item{height:50px;background:rgb(240,240,240);}");
    if(ID<0) log_list->setStyleSheet("QListWidget{background:rgb(240,240,240);border:none;}"
                                     "QListWidget::item{height:65px;background:rgb(240,240,240);}");
    log_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    log_list->hide();
    //Test--
//    for(int k=rand()%10+1;k>=0;k--)
//    {
//        LogListItem *log_item=new LogListItem();
//        log_item->setMsg(rand()&1?"MESSAGE.":"MESSAFFGEGAGAG");
//        addLogItem(log_list,rand()%3,log_item);
//    }
    //--Test
    connect(log_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(slot_getMarkdownLog(QListWidgetItem*)));
    all_log_list.append(log_list);
    if(ID>0) Cloud::gethand()->sendFriendInfoRequest(ID);
    return friend_item;
}
void MainWindow::addLogItem(QListWidget* log_list,int ID,LogListItem* log_item)
{
    if(ID==myID) log_item->setMyLog();
    QListWidgetItem *newItem = new QListWidgetItem();
    log_list->insertItem(ui->listWidget_log->count(),newItem);
    log_list->setItemWidget(newItem,log_item);
}

void MainWindow::on_pushButton_userName_clicked()
{
    iw->close();
    iw=new InfoWindow(myID);
    iw->show();
}

void MainWindow::on_pushButton_friendName_clicked()
{
    if(curID<0) return;
    QString id=ui->label_friendID->text().mid(4);
    qDebug()<<id;
    iw->close();
    iw=new InfoWindow(id.toInt());
    iw->show();
}

void MainWindow::on_pushButton_func1_clicked()
{
    mdw->hide(),mdw->reset(),mdw->show();
}

void MainWindow::slot_sendMarkdown(QString msg)
{

    qDebug()<<"Send MDmsg:"<<msg;

    QString str_msg = "MESSAGE"+
            MSG_DATA_SPLIT+
            QString::number(myID)+
            MSG_DATA_SPLIT+
            ui->label_friendID->text().mid(4)+
            MSG_DATA_SPLIT+
            QString(31,'m')+
            msg;
    Cloud::gethand()->send(myID,
                           curID,
                           str_msg);
    LogListItem *log_item=new LogListItem(myID);
    log_item->setMd(msg);
    log_item->setID(myID);
    if(curID<0) log_item->setGroupLog();
    addLogItem(ui->listWidget_log,myID,log_item);
}



void MainWindow::slot_getMarkdownLog(QListWidgetItem* item)
{
    qDebug()<<"slot_getMarkdownLog()";
    LogListItem *log_item = (LogListItem*)ui->listWidget_log->itemWidget(item);
    if(log_item->md_msg=="") return;
    ui->listWidget_log->scrollToBottom();
    qDebug()<<"emit sig_getMarkdown():"<<log_item->md_msg;
    emit sig_getMarkdown(log_item->md_msg);
}

void MainWindow::slot_getMessage(const Message& msg)
{
    QStringList list_msg = msg.deCode();

    int senderID=list_msg[1].toInt();
    int receiveID=list_msg[2].toInt();

    if(!GlobalData::id2PInfo.contains(senderID))
    {
        GlobalData::id2PInfo[senderID] = new PublicInfo();
        Cloud::gethand()->sendFriendInfoRequest(senderID);
    }

    QString str_msg = list_msg[3];
    Cloud::gethand()->send(myID,CLOUD,"RECEIVE_OK");
    qDebug()<<"senderID"<<senderID;
    qDebug()<<"receiveID"<<receiveID;

    int id;
    if(receiveID<0) id=receiveID;
    else{
        if(senderID==myID) id=receiveID;
        else id=senderID;
    }
    qDebug()<<id;
    if(receiveID<0){
        //group
        if(!friend_pos.contains(id))
            addFriendItem(id);
        int pos = friend_pos[id];
        FriendListItem *fri_item=(FriendListItem*)ui->listWidget_friend->itemWidget(ui->listWidget_friend->item(pos));
        if(id!=curID) fri_item->setDot(true);
        fri_item->setSign("Have fun with friends!");
        LogListItem *log_item=new LogListItem(senderID);
        log_item->setID(senderID);
        log_item->setGroupLog();
        if(str_msg.length()<=30) log_item->setMsg(str_msg);
        else log_item->setMsg("[Markdown]"),log_item->setMd(str_msg.mid(31));
        addLogItem(all_log_list[pos], senderID, log_item);
    }
    else{
        // p2p
        if(!friend_pos.contains(id))
            addFriendItem(id);
        int pos = friend_pos[id];
        FriendListItem *fri_item=(FriendListItem*)ui->listWidget_friend->itemWidget(ui->listWidget_friend->item(pos));
        if(id!=curID) fri_item->setDot(true);
        //fri_item->setSign(str_msg);
        LogListItem *log_item=new LogListItem(senderID);
        log_item->setID(senderID);
        if(str_msg.length()<=30) log_item->setMsg(str_msg);
        else log_item->setMd(str_msg.mid(31));
        addLogItem(all_log_list[pos], senderID, log_item);
    }


    //收到消息，和socket的readyRead()连接
    //若列表内无该用户，使用addFriendItem()添加
    //向其消息列表中添加消息addLogItem()
    //新消息提醒fri_item->setDot(true)
}



void MainWindow::slot_MyInfoUpdate(){
    PublicInfo *myInfo = GlobalData::id2PInfo[myID];
    QPixmap icon=QPixmap(":/Resources/icon/("+QString::number(myInfo->getHeadImgID())+").png");
    ui->label_icon->setPixmap(icon.scaled(ui->label_icon->size()));
    ui->pushButton_userName->setText(myInfo->getNickName());
    ui->pushButton_userName->adjustSize();
    ui->label_userID->setText("ID: "+QString::number(myID));
    ui->label_signiture->setText(myInfo->getLabel());
}

void MainWindow::slot_loadFriendList(const Message &msg){
    int friendID = msg.deCode()[1].toInt();
    qDebug()<<"Receive a friend/group id "<<friendID;
    addFriendItem(friendID);
}


void MainWindow::slot_getHistoryMessage(const Message &msg){
    qDebug()<<"FRIEND_HISTORY success";
    qDebug()<<Message(msg.toString()).toString();
    QStringList list = msg.getMessageData().split(MSG_DATA_SPLIT);
    qDebug()<<list[list.size()-2]+list[list.size()-1];
    Message true_msg(list[list.size()-2]+list[list.size()-1]);

    QString str_msg = "MESSAGE"+
            MSG_DATA_SPLIT+
            QString::number(true_msg.getSenderID())+
            MSG_DATA_SPLIT+
            QString::number(true_msg.getReceiverID())+
            MSG_DATA_SPLIT+
            true_msg.getMessageData();
    true_msg = Message(true_msg.getDatetime(),
                       str_msg,
                       true_msg.getSenderID(),
                       true_msg.getReceiverID());
    qDebug()<<true_msg.toString();
    slot_getMessage(true_msg);
}

void MainWindow::slot_Error(const Message& msg)
{
    QString err = msg.getMessageData().mid(1);
    QMessageBox msg_box;
    msg_box.setWindowTitle("Error!");
    msg_box.setText(err);
    msg_box.exec();
    if(err=="ERROR: FRIEND_ADD_ERROR"||err=="ERROR: GROUP_ADD_ERROR")
        ui->lineEdit_add->setEnabled(true);
}
