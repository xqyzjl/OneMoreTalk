#include "tcpserver.h"

TcpServer* TcpServer::tcpserverhand = nullptr;

TcpServer::TcpServer(QObject* parent) : QObject(parent)
{
    auto name = hostInfo.localHostName();
    hostInfo.setHostName(name);
    hostInfo.lookupHost(name,this,&TcpServer::slot_mid_getHostIP);
}

bool TcpServer::isListening() {
    if (m_server.isListening())
        return true;
    else
        return false;
}

void TcpServer::startServer(QString ip, QString port) {
    qDebug() << "running";

    hostAddress.setAddress(ip);
    if (m_server.listen(hostAddress, port.toInt())) {
        qDebug() << "listening";
        connect(&m_server, &deriveServer::sig_newConnect,
                this,&TcpServer::slot_server_addClient);
        connect(&m_server, &deriveServer::sig_readyRead,
                this,&TcpServer::slot_server_readData);

        connect(&m_server, &deriveServer::sig_disconnected,
                this,&TcpServer::slot_server_delClient);

        emit sig_display_startServer();
    }
    else {
        qDebug() << "failed to start server.";
    }

}

void TcpServer::stopServer() {
    disconnect(&m_server, &deriveServer::sig_newConnect,
            this,&TcpServer::slot_server_addClient);
    disconnect(&m_server, &deriveServer::sig_readyRead,
            this,&TcpServer::slot_server_readData);
    disconnect(&m_server, &deriveServer::sig_disconnected,
            this,&TcpServer::slot_server_delClient);
    clientMap.clear();
    m_server.close();
}

void TcpServer::slot_mid_getHostIP(QHostInfo info) {
    GlobalData::sleep(1000);
    emit sig_getHostIP(info);
}

void TcpServer::slot_server_addClient(int handle, QTcpSocket *socket) {
    clientMap.insert(handle,socket);
    emit sig_display_clientLogIn(socket->peerAddress().toString() + " joined the server.");
}

void TcpServer::slot_server_readData(int handle, const QByteArray &databyte) {
    qDebug() << "reading data";
    QTcpSocket *socket = clientMap.value(handle);
    if (socket == nullptr) return;
    QString data = QString::fromStdString(databyte.toStdString());
    emit sig_display_clientSendMsg(socket->peerAddress().toString() + " sent a msg");

    QStringList dataList = data.split(GlobalData::MSG_MSG_SPLIT());
    for (auto dataPiece : dataList) {
        if (dataPiece != "") {
            qDebug() << dataPiece << ' ' << socket->peerAddress();
            emit sig_modifyMsg(dataPiece,socket);
        }
    }

    //QString re = "Re:";
    //re.append(data);
    //socket->write(re.toLatin1());

}

void TcpServer::slot_server_delClient(int handle) {
    QTcpSocket *socket = clientMap.value(handle);
    if (socket == nullptr) return;
    emit sig_display_clientLogOut(socket->peerAddress().toString() + " left the server."); // to main window
    emit sig_manager_clientLogOut(socket); // to manager
    clientMap.remove(handle);
//    delete socket;
}
/*
void TcpServer::slot_server_sendData(QString datastr, QTcpSocket* socket) {
    socket->write(datastr.toLatin1());
}
*/
