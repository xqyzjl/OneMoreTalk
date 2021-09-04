#include <QApplication>

#include "mainwindow.h"
#include "tcpserver.h"
//#include "mysql.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    Mysql *sqlhand = Mysql::gethand();
//    sqlhand->openDatabase();



    MainWindow mainWindow;
    mainWindow.show();


    return a.exec();
}
