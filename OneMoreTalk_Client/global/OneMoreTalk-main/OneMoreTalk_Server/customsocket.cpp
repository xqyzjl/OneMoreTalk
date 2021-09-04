#include "customsocket.h"

customSocket::customSocket(const int handle) : m_handle(handle)
{
    this -> setSocketDescriptor(m_handle);

    connect(this, &customSocket::readyRead,
            this, &customSocket::slot_readData);
    connect(this, &customSocket::disconnected,
            this, &customSocket::slot_disconnected);
}

void customSocket::slot_readData() {
    QByteArray databyte = readAll();
    qDebug() << "custom socket read";
    emit sig_readyRead(m_handle, databyte);
}

void customSocket::slot_disconnected() {
    emit sig_disconnected(m_handle);
}

