#ifndef CUSTOMSOCKET_H
#define CUSTOMSOCKET_H

#include <QObject>
#include <QTcpSocket>

class customSocket : public QTcpSocket
{
    Q_OBJECT
public:
    customSocket(const int handle);
    void slot_readData();

private:
    int m_handle;

signals:
    void sig_readyRead(int, const QByteArray &);
    void sig_disconnected(int);

private slots:
    void slot_disconnected();

};

#endif // CUSTOMSOCKET_H
