#ifndef MYUDPCASTMULTICAST_H
#define MYUDPCASTMULTICAST_H

#include <QObject>
#include <QDebug>
#include <QMetaObject>
#include <QThread>
#include "HPSocket.h"
#pragma execution_character_set("utf-8") //防止中文乱码

class MyUdpMultiCastListener : public QObject, public CUdpCastListener
{
    Q_OBJECT
public:
     MyUdpMultiCastListener(QObject *parent = nullptr);
     QString getReceiveMsg();

private:
    /*回调函数，自主触发*/
    EnHandleResult OnPrepareConnect(IUdpCast* pSender, CONNID dwConnID, SOCKET socket);
    EnHandleResult OnConnect(IUdpCast* pSender, CONNID dwConnID);
    EnHandleResult OnSend(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    EnHandleResult OnReceive(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    EnHandleResult OnClose(IUdpCast* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);

private:
    static QString receiveMsg;

signals:
    //void receiveComplete(); //接收完成信号
};


class MyUdpCast : public QObject
{
    Q_OBJECT
public:
    explicit MyUdpCast();

    void connect(const QString &ipv4, uint16_t port);
    void write(const QString &data);
    void closeSocket();

private:
    IUdpCast *pUdpCast = HP_Create_UdpCast(new MyUdpMultiCastListener());

signals:
    void connectComplete(); //连接完成信号
    void sendComplete();    //发送完成信号
    void receiveComplete(); //接收完成信号
    void closeComplete();   //关闭完成信号
};


#endif // MYUDPCASTMULTICAST
