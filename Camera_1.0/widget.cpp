#include "widget.h"
#include "ui_widget.h"
#include "QDebug"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_but_connect_clicked()
{
    /*pUdpCast->SetCastMode(CM_MULTICAST);
    pUdpCast->SetMultiCastLoop(TRUE);
    pUdpCast->SetMultiCastTtl(6);
    bool ret =  pUdpCast->Start(LPCTSTR(L"260.0.0.80"), 6566, false, LPCTSTR(L"0.0.0.0"));
    if(!ret)
    {
        DWORD error = GetLastError();
        qDebug()<<error;
    }
    else
    {
       qDebug()<<"888";
    }*/
}

void Widget::on_but_send_clicked()
{
    /*BYTE data = 1;
    bool ret = pUdpCast->Send(&data, sizeof(data));
    if(!ret)
    {
      DWORD error = SYS_GetLastError();
      qDebug()<<error;
      qDebug()<<"send";
    }*/
}

/**
 * @brief 读取UDP数据报
 */
void Widget::on_readyRead_clicked()
{
    /*pUdpCast->Stop();
    qDebug()<<"stop";*/
}

