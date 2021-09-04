#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>
#include <global/globaldata.h>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    LoginWindow* lw = (LoginWindow*)GlobalData::get_loginWindow();
    lw->show();
    return a.exec();
}
