#ifndef FRIENDLISTITEM_H
#define FRIENDLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QListWidgetItem>

class FriendListItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendListItem(QWidget *parent = nullptr);
    void setID(int id);
    void setDot(bool);
    void setSign(QString);
    QPixmap getIcon() const {return *(icon->pixmap());}
    QString getName() const {return name->text();}
    QString getSign() const {return sign->text();}
    int id,pos;

private:
    QLabel *icon,*name,*sign,*dot;

private slots:
    void slot_PinfoChanged();
};

#endif // FRIENDLISTITEM_H
