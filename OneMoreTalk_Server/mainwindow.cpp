#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = TcpServer::gethand();
//  服务器启动运行
    connect(m_server, &TcpServer::sig_getHostIP,
            this, &MainWindow::slot_getHostIP);
//  消息动作显示
    connect(m_server, &TcpServer::sig_display_startServer,
            this, &MainWindow::slot_display_startServer);
    connect(m_server, &TcpServer::sig_display_clientLogIn,
            this, &MainWindow::slot_display_clientLogIn);
    connect(m_server, &TcpServer::sig_display_clientLogOut,
            this, &MainWindow::slot_display_clientLogOut);
//    connect(m_server, &TcpServer::sig_display_clientSendMsg,
//            this, &MainWindow::slot_display_clientSendMsg);
    connect(&m_manager, &ServerManager::sig_display_activity,
            this, &MainWindow::slot_display_clientSendMsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_getHostIP(QHostInfo info) {
    QList<QHostAddress> addressList = info.addresses();
    for (auto address : addressList) {
        ui->comboBox->addItem(address.toString());
    }
}



void MainWindow::slot_display_startServer() {
    ui->pushButton->setText("Running");
}
void MainWindow::slot_display_clientLogIn(QString str) {
    ui->listWidget->addItem(str);
}
void MainWindow::slot_display_clientLogOut(QString str) {
    ui->listWidget->addItem(str);
}
void MainWindow::slot_display_clientSendMsg(QString str) {
    ui->listWidget->addItem(str);
}


void MainWindow::on_pushButton_clicked()
{
    if (!m_server->isListening()) {
        QString IP = ui->comboBox->currentText();
        QString PORT = ui->lineEdit->text();
        m_server->startServer(IP, PORT);
        ui->listWidget->addItem("[Server started successfully]");
        ui->listWidget->addItem("--" + IP+":"+PORT);
    }
    else {
        m_server->stopServer();
        ui->pushButton->setText("Ready to Start");
        ui->listWidget->addItem("[Server closed]");
    }
}
