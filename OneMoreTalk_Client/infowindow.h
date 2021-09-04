#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "global/globaldata.h"

#include <QDialog>
#include <QDebug>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    InfoWindow(int ID);
    ~InfoWindow();

private slots:
    void on_pushButton_edit_clicked();

    void on_pushButton_submit_clicked();

private:
    Ui::InfoWindow *ui;
};

#endif // INFOWINDOW_H
