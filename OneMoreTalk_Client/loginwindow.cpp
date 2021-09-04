#include "loginwindow.h"

#include "mainwindow.h"
#include "global/globaldata.h"

const QString MSG_DATA_SPLIT=GlobalData::MSG_DATA_SPLIT();
Cloud* cloud;


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->lineEdit_server->setText("10.194.189.213:10086");
    cloud = Cloud::gethand();
    connect(cloud, SIGNAL(SIG_LOGIN_OK(Message)),
            this, SLOT(slot_LOGIN_OK(Message)));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_connect_clicked()   // ###连接
{
    QString IP_port = ui->lineEdit_server->text();
    QStringList IP_port_list = IP_port.split(':');
    bool f = cloud->set(IP_port_list[0],IP_port_list[1].toInt());
    if(f)
    {
        ui->pushButton_connect->setText("Connected");
        ui->pushButton_connect->setEnabled(false);
    }
    else
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle("Error!");
        msg_box.setText("Cannot connect to server!");
        msg_box.exec();
    }
}

void LoginWindow::on_pushButton_login_clicked()
{
    on_pushButton_connect_clicked();
    QString msg_data="LOGIN_QUEST"+MSG_DATA_SPLIT+
            ui->lineEdit_2->text()+MSG_DATA_SPLIT+
            ui->lineEdit_pw->text();
    cloud->send(ui->lineEdit_2->text().toInt(),
                CLOUD,
                msg_data);
}


void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
        on_pushButton_login_clicked();
}

void LoginWindow::on_pushButton_signup_clicked()
{
    SignupWindow *sw=new SignupWindow();
    sw->show();
}

void LoginWindow::on_pushButton_forget_clicked()
{
    ForgetWindow *fw=new ForgetWindow();
    fw->show();

}


void LoginWindow::slot_LOGIN_OK(Message msg){
    GlobalData::MyId = ui->lineEdit_2->text().toInt();
    GlobalData::id2PInfo[GlobalData::MyId] = new PublicInfo;
    MainWindow* mainwindow = (MainWindow*)GlobalData::get_mainWindow();
    mainwindow->show();
    this->close();
}
void LoginWindow::slot_Error(const Message& msg)
{
    QString err = msg.getMessageData().mid(1);
    QMessageBox msg_box;
    msg_box.setWindowTitle("Error!");
    msg_box.setText(err);
    msg_box.exec();
}

void LoginWindow::on_lineEdit_server_textChanged(const QString &arg1)
{
    ui->pushButton_connect->setText("Connect");
    ui->pushButton_connect->setEnabled(true);
}
