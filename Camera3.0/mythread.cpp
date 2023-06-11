#include "mythread.h"
//UIUpdater *UIUpdater::updater = NULL;


/*--------------@brief：UIUpdater构造函数-------------*/
UIUpdater::UIUpdater(QObject *parent) : QObject(parent)
{
    moveToThread(&workerThread);
    workerThread.start();
}


/*--------------@brief：UIUpdater析构函数-------------*/
UIUpdater::~UIUpdater()
{
    workerThread.quit();
    workerThread.wait();
}


/*--------------@brief：处理'OnReceive'回调函数接收的数据-------------*/
void UIUpdater::processData(QString data)
{
    //处理数据

    //发送信号通知更新用户界面
    emit updateUI(data);
}
