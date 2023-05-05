#include "MyUdpMultiCast.h"

/**
 * @brief 启动UDP组播
 */
bool MyUdpCast::connect(const QString &ipv4, uint16_t port)
{
    pUdpCast->SetCastMode(CM_MULTICAST); //组播模式
    pUdpCast->SetMultiCastLoop(TRUE);    //启用组播环路
    pUdpCast->SetMultiCastTtl(6);        //设置组播的报文
    bool ret =  pUdpCast->Start(LPCTSTR(L"260.0.0.80"), port, false, LPCTSTR(L"0.0.0.0"));
    if(!ret)
    {
        DWORD error = GetLastError();
        qDebug()<<error;
    }
    else
    {
       qDebug()<<"加入组播成功";
    }
}

/**
 * @brief 发送数据
 */
bool write(const std::string &data)
{


}

/**
 * @brief 退出组播
 */
