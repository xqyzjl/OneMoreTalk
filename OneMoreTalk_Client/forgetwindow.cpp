#include "forgetwindow.h"
#include "ui_forgetwindow.h"

ForgetWindow::ForgetWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetWindow)
{
    ui->setupUi(this);
    connect(Cloud::gethand(),SIGNAL(SIG_PASSWORD_PROTECT_QUESTION(const Message&)),
            this,SLOT(slot_ProtectQue(const Message&)));
    connect(Cloud::gethand(),SIGNAL(SIG_PASSWORD_FIND_OK(const Message&)),
            this,SLOT(slot_PwFindOK(const Message&)));
    connect(Cloud::gethand(),SIGNAL(SIG_ERROR(const Message&)),
            this,SLOT(slot_Error(const Message&)));
}

ForgetWindow::~ForgetWindow()
{
    delete ui;
}

void ForgetWindow::on_pushButton_clicked()
{
    QString str_msg = "PASSWORD_PROTECT_ANSWER"
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_3->text()
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_4->text();
    Cloud::gethand()->send(ui->lineEdit_1->text().toUInt(),CLOUD,str_msg);
}

void ForgetWindow::on_lineEdit_1_editingFinished()
{
    QString str_msg = "PASSWORD_FIND"
                      +GlobalData::MSG_DATA_SPLIT()
                      +ui->lineEdit_1->text();
    Cloud::gethand()->send(ui->lineEdit_1->text().toUInt(),CLOUD,str_msg);
}

void ForgetWindow::slot_ProtectQue(const Message &msg)
{
    QStringList list=msg.deCode();
    ui->plainTextEdit_2->setPlainText(list[1]);
}
void ForgetWindow::slot_PwFindOK(const Message &msg)
{
    QMessageBox msg_box;
    msg_box.setWindowTitle("OK!");
    msg_box.setText("Password set to: "+ui->lineEdit_4->text());
    msg_box.exec();
}
void ForgetWindow::slot_Error(const Message &msg)
{
    QMessageBox msg_box;
    msg_box.setWindowTitle("Error!");
    msg_box.setText(msg.getMessageData());
    msg_box.exec();
    msg_box.close();
}
