#include "MyUdpMultiCast.h"
QString MyUdpMultiCastListener::receiveMsg = " ";

MyUdpMultiCastListener::MyUdpMultiCastListener(QObject *parent)
                       :QObject(parent)
{



}


/*--------------@brief：MyUdpCast构造函数-------------*/
MyUdpCast::MyUdpCast()
{


}


/*--------------@brief：准备连接通知-------------*/
EnHandleResult MyUdpMultiCastListener::OnPrepareConnect(IUdpCast* pSender, CONNID dwConnID, SOCKET socket)
{
    Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(socket); //形参未使用，防止警告
    qDebug()<<"OnPrepareConnect";
    return HR_OK;
}


/*--------------@brief：与服务端成功建立连接时，'Socket'监听器将收到该通知，触发连接完成信号-------------*/
EnHandleResult MyUdpMultiCastListener::OnConnect(IUdpCast* pSender, CONNID dwConnID)
{
    Q_UNUSED(pSender);Q_UNUSED(dwConnID); //形参未使用，防止警告
    qDebug()<<"OnConnect";
    return HR_OK;
}


/*--------------@brief：成功发送数据后，'Socket'监听器将收到该通知，触发发送完成信号-------------*/
EnHandleResult MyUdpMultiCastListener::OnSend(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(pData);Q_UNUSED(iLength); //形参未使用，防止警告
    //emit sendComplete();
    qDebug() <<"OnSend";
    return HR_OK;
}


/*--------------@brief：成功接收数据通知，触发接收完成信号-------------*/
EnHandleResult MyUdpMultiCastListener::OnReceive(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    Q_UNUSED(pSender);Q_UNUSED(dwConnID);
    QByteArray byteArray(reinterpret_cast<const char*>(pData), iLength);
    QString strData(byteArray);
    receiveMsg = strData;
    qDebug() << receiveMsg;
    qDebug() <<"OnReceive";
    return HR_OK;
}


/*--------------@brief：通信发生错误后，'Socket'监听器将收到该通知，并关闭连接-------------*/
EnHandleResult MyUdpMultiCastListener::OnClose(IUdpCast* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
    Q_UNUSED(pSender);Q_UNUSED(dwConnID);Q_UNUSED(enOperation);Q_UNUSED(iErrorCode);
    qDebug() <<"OnClose";
    return HR_OK;
}


/*--------------@brief：将接受的消息传到'widget'文件里-------------*/
QString MyUdpMultiCastListener::getReceiveMsg()
{
    return receiveMsg;
}


/*--------------@brief：启动UDP组播-------------*/
void MyUdpCast::connect(const QString &ipv4, uint16_t port)
{
    std::wstring wlpstr = ipv4.toStdWString(); //QString转换为LPCWSTR
    LPCWSTR lpcwStr = wlpstr.c_str();

    pUdpCast->SetCastMode(CM_MULTICAST); //组播模式
    pUdpCast->SetMultiCastLoop(TRUE);    //启用组播环路
    pUdpCast->SetMultiCastTtl(6);        //设置组播的报文
    bool ret =  pUdpCast->Start(lpcwStr, port, false, LPCTSTR(L"0.0.0.0")); //采用同步连接方式，即连接成功再返回TURE
    //bool ret =  pUdpCast->Start(LPCTSTR(L"226.0.0.80"), port, false, LPCTSTR(L"0.0.0.0"));
    if(!ret)
    {
        DWORD error = GetLastError();
        qDebug()<<"组播启动失败，错误代码："<<error;
    }
    else
    {
       emit connectComplete(); //触发连接完成信号，更新'ui'界面
       qDebug()<<"加入组播成功";
    }
}


/*--------------@brief：发送数据-------------*/
void MyUdpCast::write(const QString &data)
{
    QByteArray byteArray = data.toUtf8();
    const BYTE* pBuffer = reinterpret_cast<const BYTE*>(byteArray.constData());
    bool ret = pUdpCast->Send(pBuffer, sizeof(pBuffer));
    if(!ret)
    {
      DWORD error = SYS_GetLastError();
      qDebug()<<"发送数据失败,错误代码："<<error;
    }
    else
    {
        emit sendComplete();    //触发发送完成信号，更新'ui'界面
        emit receiveComplete(); //
        qDebug()<<"成功发送数据";
    }
}


/*--------------@brief：退出组播-------------*/
void MyUdpCast::closeSocket()
{
     bool ret = pUdpCast->Stop();
     if(!ret)
     {
         DWORD error = GetLastError();
         qDebug()<<"退出组播失败,错误代码："<<error;
     }
     else
     {
         emit closeComplete(); //触发关闭完成信号，更新'ui'界面
         qDebug()<<"成功退出组播";
     }
}
