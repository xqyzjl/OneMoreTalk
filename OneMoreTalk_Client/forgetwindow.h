#ifndef FORGETWINDOW_H
#define FORGETWINDOW_H

#include "cloud.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ForgetWindow;
}

class ForgetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetWindow(QWidget *parent = nullptr);
    ~ForgetWindow();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_1_editingFinished();

    void slot_ProtectQue(const Message&);
    void slot_PwFindOK(const Message&);
    void slot_Error(const Message&);


private:
    Ui::ForgetWindow *ui;
};

#endif // FORGETWINDOW_H
