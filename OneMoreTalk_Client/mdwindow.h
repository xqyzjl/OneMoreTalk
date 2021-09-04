#ifndef MDWINDOW_H
#define MDWINDOW_H

#include "loglistitem.h"

#include <QDialog>
#include <QDebug>
#include <QMainWindow>

namespace Ui {
class MDWindow;
}

class MDWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MDWindow(QWidget *parent = nullptr);
    ~MDWindow();
    void reset();

    QMainWindow *mw;


private slots:
    void on_textEdit_edit_textChanged();

    void on_pushButton_clicked();

    void slot_getMarkdown(QString);


private:
    Ui::MDWindow *ui;

signals:
    void sig_sendMarkdown(QString);

};

#endif // MDWINDOW_H
