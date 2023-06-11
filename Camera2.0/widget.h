#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qnetworkinterface.h>
#include "MyUdpMultiCast.h"
#include "HPSocket.h"

#pragma execution_character_set("utf-8") //防止中文乱码

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void DisplayMsgInTextEdit();
    QString getLocalIP();

public slots:
    void on_but_connect_clicked();
    void on_MulticastMsg_clicked();
    void on_but_close_clicked();

    void on_displayConnectMsg();
    void on_displaySendMsg();
    void on_displayCloseMsg();
    void on_displayReceiveMsg();

private:
    Ui::Widget *ui;
    MyUdpCast *mMyUdpCast;
    MyUdpMultiCastListener *myListener;
};
#endif // WIDGET_H
