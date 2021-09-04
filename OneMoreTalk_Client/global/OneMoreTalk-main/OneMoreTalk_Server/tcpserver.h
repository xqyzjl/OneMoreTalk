#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QMap>
#include "customsocket.h"
#include "deriveserver.h"


class TcpServer : public QObject
{
    Q_OBJECT
public:
    static TcpServer* gethand() {
        if (tcpserverhand == nullptr)
            tcpserverhand = new TcpServer();
        return tcpserverhand;
    }
//  服务器状态控制
    bool isListening();
    void startServer(QString ip, QString port);
    void stopServer();


private:
    explicit TcpServer(QObject* parent = nullptr);
    static TcpServer* tcpserverhand;

    QHostInfo hostInfo;
    QHostAddress hostAddress;
    QMap<int,QTcpSocket *> clientMap;

    deriveServer m_server;


signals:
//  服务器状态改变信号 to mainwindow
    void sig_display_startServer();
    void sig_getHostIP(QHostInfo);

//  活动消息显示信号 to mainwindow
    void sig_display_clientLogIn(QString);
    void sig_display_clientLogOut(QString);
    void sig_display_clientSendMsg(QString);

//  活动消息处理信号 to manager
    void sig_modifyMsg(QString, QTcpSocket*);
    void sig_manager_clientLogOut(QTcpSocket*);

private slots:
//
    void slot_mid_getHostIP(QHostInfo);

//  服务端接收活动的槽
    void slot_server_readData(int, const QByteArray &);
    void slot_server_addClient(int, QTcpSocket *);
    void slot_server_delClient(int);
    void slot_server_sendData(QString, QTcpSocket*);

};

#endif // TCPSERVER_H
