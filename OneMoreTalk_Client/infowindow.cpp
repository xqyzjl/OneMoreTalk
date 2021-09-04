#include "infowindow.h"
#include "ui_infowindow.h"

#include<cloud.h>

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
}
InfoWindow::InfoWindow(int ID) : ui(new Ui::InfoWindow)
{
    //qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@"<<GlobalData::id2PInfo[ID]->toString();
    ui->setupUi(this);
    for(int i=0;i<=30;i++)
    {
        QPixmap user_icon;
        user_icon.load(":/Resources/icon/("+QString::number(i)+").png");
        ui->comboBox_icon->addItem((QIcon)user_icon,"");
    }
    PublicInfo *info = GlobalData::id2PInfo[ID];
    ui->comboBox_icon->setCurrentIndex(info->getHeadImgID());
    ui->lineEdit_name->setText(info->getNickName());
    ui->label_userID->setText("ID: "+QString::number(info->getUserID()));
    ui->lineEdit_sign->setText(info->getLabel());
    ui->lineEdit_age->setText(QString::number(info->getAge()));
    ui->comboBox_gender->setCurrentIndex(info->getSex());
    if(ID!=GlobalData::MyId)
    {
        ui->pushButton_edit->hide();
        ui->pushButton_submit->hide();
    }
}


InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::on_pushButton_edit_clicked()
{
    ui->label_cover->hide();
    ui->lineEdit_name->setReadOnly(false);
    ui->lineEdit_name->setStyleSheet("background:rgba(255,255,255,128);");
    ui->lineEdit_sign->setReadOnly(false);
    ui->lineEdit_sign->setStyleSheet("background:rgba(255,255,255,128)");
    ui->lineEdit_age->setReadOnly(false);
    ui->lineEdit_age->setStyleSheet("background:rgba(255,255,255,128)");
    ui->comboBox_icon->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    ui->comboBox_icon->setStyleSheet("QComboBox{background:rgba(0,0,0,0);border:none;}"
                                     "QComboBox::item{background:white;}");
    ui->comboBox_gender->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    ui->comboBox_gender->setStyleSheet("QComboBox{background:rgba(255,255,255,128);}"
                                       "QComboBox::item{background:white;}");
}

void InfoWindow::on_pushButton_submit_clicked()
{
    //界面设置
    ui->label_cover->show();
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_name->setStyleSheet("background:rgba(0,0,0,0);border:none;");
    ui->lineEdit_sign->setReadOnly(true);
    ui->lineEdit_sign->setStyleSheet("background:rgba(0,0,0,0);border:none;");
    ui->lineEdit_age->setReadOnly(true);
    ui->lineEdit_age->setStyleSheet("background:rgba(0,0,0,0);border:none;");
    ui->comboBox_icon->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->comboBox_icon->setStyleSheet("QComboBox{background:rgba(0,0,0,0);border:none;}"
                                     "QComboBox::drop-down{border-style:none;}");
    ui->comboBox_icon->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->comboBox_gender->setStyleSheet("QComboBox{background:rgba(0,0,0,0);border:none;}"
                                       "QComboBox::drop-down{border-style:none;}");
    //发送Message
    PublicInfo info(ui->comboBox_icon->currentIndex(),
                    GlobalData::MyId,
                    ui->lineEdit_name->text(),
                    ui->comboBox_gender->currentIndex(),
                    ui->lineEdit_sign->text(),
                    ui->lineEdit_age->text().toInt()
                );
    QString str_msg = "USER_INFO_UPDATE_REQUEST"
                      +GlobalData::MSG_DATA_SPLIT()
                      +info.toString();
    Cloud::gethand()->send(GlobalData::MyId,CLOUD,str_msg);
    GlobalData::id2PInfo[GlobalData::MyId]->set(info);
}
