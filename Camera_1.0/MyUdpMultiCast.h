#ifndef MYUDPCASTMULTICAST_H
#define MYUDPCASTMULTICAST_H
#include <QObject>
#include "HPSocket.h"
#include <QDebug>
//#include "widget.h"

class MyUdpMultiCastListener : public QObject, public CUdpCastListener
{
    Q_OBJECT
public:
    explicit MyUdpMultiCastListener(QObject *parent = nullptr) : QObject(parent) {};

private:
    /*回调函数，自主触发*/
    EnHandleResult OnPrepareConnect(IUdpCast* pSender, CONNID dwConnID, SOCKET socket)
    {
        Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(socket); //形参未使用，防止警告
        qDebug()<<"OnPrepareConnect";
        return HR_OK;
    }

    EnHandleResult OnConnect(IUdpCast* pSender, CONNID dwConnID)
    {
        qDebug()<<"OnConnect";
        return HR_OK;
    }

    EnHandleResult OnSend(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
    {
        Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(pData);Q_UNUSED(iLength); //形参未使用，防止警告
        qDebug() <<"onsend";
        return HR_OK;
    }

    EnHandleResult OnReceive(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
    {
        Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(pData);Q_UNUSED(iLength);
        qDebug() <<"OnReceive";
        return HR_OK;

    }

    EnHandleResult OnClose(IUdpCast* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
    {
        qDebug() <<"OnClose";
        return HR_OK;
    }
};

class MyUdpCast
{
public:
    bool connect(const QString &ipv4, uint16_t port);
    bool write(const std::string &data);
    bool closeSocket();

private:
    IUdpCast *pUdpCast = HP_Create_UdpCast(new MyUdpMultiCastListener());

};


#endif // MYUDPCASTMULTICAST
