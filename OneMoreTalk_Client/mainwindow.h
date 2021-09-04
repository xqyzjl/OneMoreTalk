#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "friendlistitem.h"
#include "loglistitem.h"
#include "infowindow.h"
#include "mdwindow.h"

#include<global/message.h>

#include <QMainWindow>
#include <QDebug>
#include <QSize>
#include <QWidget>
#include <QKeyEvent>
#include <QListWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMap<int,int> friend_pos;
    QMap<int,int> had_load_message;
    static int myID;
    int curID;
    void setMarkdown(QString);
    void addMessage();
private slots:
    void on_listWidget_friend_itemClicked(QListWidgetItem *item);

    void on_pushButton_send_clicked();

    void on_lineEdit_send_textChanged(const QString &arg1);

    void on_pushButton_add_clicked();

    void on_pushButton_userName_clicked();

    void on_pushButton_friendName_clicked();

    void on_pushButton_func1_clicked();

    void slot_sendMarkdown(QString);
    void slot_getMarkdownLog(QListWidgetItem*);
    void slot_getMessage(const Message &);
    void slot_MyInfoUpdate();
    void slot_loadFriendList(const Message &msg);
    void slot_addfriend(const Message &msg);
    void slot_getHistoryMessage(const Message &msg);
    void slot_Error(const Message& msg);
private:
    Ui::MainWindow *ui;
    QList<QListWidget*> all_log_list;
    InfoWindow *iw;
    MDWindow *mdw;
    QMessageBox msg_box;

    void hideRight();
    void showRight();
    FriendListItem* addFriendItem(int ID);
    void addLogItem(QListWidget* log_list,int ID,LogListItem* log_item);
    void keyPressEvent(QKeyEvent *event);

signals:
    void sig_getMarkdown(QString);
};
#endif // MAINWINDOW_H
