#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <signupwindow.h>
#include <forgetwindow.h>
#include "ui_loginwindow.h"
#include "cloud.h"

#include <QDialog>
#include <QKeyEvent>
#include <QDebug>
#include <global/message.h>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_login_clicked();
    void on_pushButton_signup_clicked();
    void on_pushButton_forget_clicked();

private:
    Ui::LoginWindow *ui;
    void keyPressEvent(QKeyEvent * event);
    bool waiting=false;

private slots:
    void slot_LOGIN_OK(Message msg);
    void slot_Error(const Message&);

    void on_lineEdit_server_textChanged(const QString &arg1);

signals:

};

#endif // LOGINWINDOW_H
