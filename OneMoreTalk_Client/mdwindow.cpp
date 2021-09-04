#include "mdwindow.h"
#include "ui_mdwindow.h"

MDWindow::MDWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MDWindow)
{
    ui->setupUi(this);
    //connect(mw,SIGNAL(sig_getMarkdown(QString)),this,SLOT(slot_getMarkdown(QString)));
}

MDWindow::~MDWindow()
{
    delete ui;
}

void MDWindow::reset()
{
    ui->textEdit_edit->setReadOnly(false);
    ui->textEdit_edit->setPlainText("");
    ui->textEdit_show->setMarkdown("");
    ui->pushButton->show();
}

void MDWindow::on_textEdit_edit_textChanged()
{
    if(ui->textEdit_edit->toPlainText().length()>60000)
        ui->textEdit_edit->setText(ui->textEdit_edit->toPlainText().left(60000));
    ui->textEdit_show->setMarkdown(ui->textEdit_edit->toPlainText());
}

void MDWindow::on_pushButton_clicked()
{
    emit sig_sendMarkdown(ui->textEdit_edit->toPlainText());
    this->close();
}



void MDWindow::slot_getMarkdown(QString msg)
{
    qDebug()<<"Get MDmsg:"<<msg;
    ui->textEdit_edit->setPlainText(msg);
    ui->textEdit_edit->setReadOnly(true);
    ui->textEdit_show->setMarkdown(msg);
    ui->pushButton->hide();
    this->show();
}
