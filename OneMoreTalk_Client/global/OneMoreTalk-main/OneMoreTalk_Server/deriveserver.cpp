#include "deriveserver.h"

deriveServer::deriveServer()
{

}

void deriveServer::incomingConnection(qintptr handle) {
    customSocket *m_socket = new customSocket(handle);
    qDebug() << "new incoming connection";
    connect(m_socket, &customSocket::sig_readyRead,
            this, &deriveServer::slot_readyRead);
    connect(m_socket, &customSocket::sig_disconnected,
            this, &deriveServer::slot_disconnected);
    qDebug() << "new incoming connection2";
    emit sig_newConnect(handle, m_socket);
}

void deriveServer::slot_readyRead(int handle, const QByteArray &databyte) {
    qDebug() << "derive server ready read";
    emit sig_readyRead(handle, databyte);
}

void deriveServer::slot_disconnected(int handle) {
    emit sig_disconnected(handle);
}
