#include "signupwindow.h"
#include "ui_signupwindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    connect(Cloud::gethand(),SIGNAL(SIG_SIGNUP_OK(const Message&)),
            this,SLOT(slot_getSignupOK(const Message&)));
    connect(Cloud::gethand(),SIGNAL(SIG_ERROR(const Message&)),
            this,SLOT(slot_getError(const Message&)));
    void SIG_SIGNUP_OK(const Message &msg);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_1->text().isEmpty() or
       ui->lineEdit_2->text().isEmpty() or
       ui->lineEdit_2->text().isEmpty() or
       ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle("Error!");
        msg_box.setText("Unallowed Empty Item!");
        msg_box.exec();
        return;
    }
    QString str_msg = "SIGNUP_QUEST"
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_1->text()
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_2->text()
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->plainTextEdit_3->toPlainText()
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_4->text();
    Cloud::gethand()->send(0,CLOUD,str_msg);
}

void SignupWindow::slot_getSignupOK(const Message& msg)
{
    QStringList list = msg.deCode();
    QMessageBox msg_box;
    msg_box.setWindowTitle("Signup OK!");
    msg_box.setText("OK! Your ID is "+list[1]+"\nPlease be sure to REMEMBER it!");
    msg_box.exec();
    this->close();
}
void SignupWindow::slot_getError(const Message& msg)
{
    QMessageBox msg_box;
    msg_box.setWindowTitle("Error!");
    msg_box.setText(msg.getMessageData().mid(1));
    msg_box.exec();
}
