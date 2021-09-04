#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include "cloud.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void on_pushButton_clicked();
    void slot_getSignupOK(const Message&);
    void slot_getError(const Message&);

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H
