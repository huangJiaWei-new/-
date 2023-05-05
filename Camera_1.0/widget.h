#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "MyUdpMultiCast.h"
#include "HPSocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //IUdpCast *pUdpCast = HP_Create_UdpCast(new MyUdpMultiCastListener());

private:
    Ui::Widget *ui;

private slots:
    void on_but_connect_clicked();
    void on_but_send_clicked();
    void on_readyRead_clicked();
};
#endif // WIDGET_H
