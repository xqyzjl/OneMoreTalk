#ifndef LOGLISTITEM_H
#define LOGLISTITEM_H

#include "cloud.h"

#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QDebug>
#include <QListWidget>

class LogListItem : public QWidget
{
    Q_OBJECT
public:
    explicit LogListItem(QWidget *parent = nullptr);
    explicit LogListItem(int _id);
    int id;
    QLabel *icon,*name,*msg;
    QString md_msg;
    void setMyLog();
    void setMsg(QString);
    void setID(int id);
    void setMd(QString);
    void setGroupLog();

private slots:
    void slot_updateMessageInfo();
};

#endif // LOGLISTITEM_H
