#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "tcpserver.h"
#include "servermanager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//  服务端本体
    TcpServer *m_server;
    ServerManager m_manager;


private slots:
    void slot_display_startServer();
    void slot_getHostIP(QHostInfo);

    void slot_display_clientLogIn(QString);
    void slot_display_clientLogOut(QString);
    void slot_display_clientSendMsg(QString);


    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
