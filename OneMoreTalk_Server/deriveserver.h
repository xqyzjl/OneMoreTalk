#ifndef DERIVESERVER_H
#define DERIVESERVER_H

#include <QObject>
#include <QTcpServer>
#include "customsocket.h"

class deriveServer : public QTcpServer
{
    Q_OBJECT
public:
    deriveServer();
    virtual void incomingConnection(qintptr handle) override;

signals:
//  带参信号传回server
    void sig_newConnect(int, QTcpSocket*);
    void sig_disconnected(int);
    void sig_readyRead(int, const QByteArray &);

private slots:
//  接收customSocket的带参信号
    void slot_readyRead(int, const QByteArray &);
    void slot_disconnected(int);

};

#endif // DERIVESERVER_H
