#include "widget.h"
#include "ui_widget.h"
#include "QDebug"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("UDP MultiCast---本机IP"+getLocalIP());

    mMyUdpCast = new MyUdpCast;
    myListener = new MyUdpMultiCastListener;
    connect(mMyUdpCast, SIGNAL(connectComplete()), this, SLOT(on_displayConnectMsg()));
    connect(mMyUdpCast, SIGNAL(sendComplete()),    this, SLOT(on_displaySendMsg()));
    connect(mMyUdpCast, SIGNAL(closeComplete()),   this, SLOT(on_displayCloseMsg()));
    connect(mMyUdpCast, SIGNAL(receiveComplete()), this, SLOT(on_displayReceiveMsg()));

}

Widget::~Widget()
{
    delete ui;
}


/*--------------@brief：点击'加入组播',启动组播------------*/
void Widget::on_but_connect_clicked()
{
    mMyUdpCast->connect(ui->MulticastAdd->text(),
                       ui->MulticastPort->text().toUShort());
}


/*--------------@brief：点击'组播消息'按钮，向组内发送数据-------------*/
void Widget::on_MulticastMsg_clicked()
{
    mMyUdpCast->write(ui->ProtocolCmd->text());
}


/*--------------@brief：点击'退出组播'按钮，关闭组播-------------*/
void Widget::on_but_close_clicked()
{
    mMyUdpCast->closeSocket();
}


/*--------------@brief：接收'Start'函数连接成功信号，在'QPlainTextEdit'里显示消息-------------*/
void Widget::on_displayConnectMsg()
{
    ui->plainTextEdit->appendPlainText("**加入组播成功");
    ui->plainTextEdit->appendPlainText("**组播IP："+ui->MulticastAdd->text());
    ui->plainTextEdit->appendPlainText("**绑定端口："+ui->MulticastPort->text());
}


/*--------------@brief：接收'send'函数发送成功信号，在'QPlainTextEdit'里显示消息-------------*/
void Widget::on_displaySendMsg()
{
    ui->plainTextEdit->appendPlainText("[mulicast] "+ui->ProtocolCmd->text());
    qDebug() << "on_displaySendMsg";

}


/*--------------@brief：接收'stop'函数发送成功信号，在'QPlainTextEdit'里显示消息-------------*/
void Widget::on_displayCloseMsg()
{
    ui->plainTextEdit->appendPlainText(getLocalIP()+" 退出组播");
}


/*--------------@brief：接收'send'函数发送成功信号，在'QPlainTextEdit'里显示消息-------------*/
void Widget::on_displayReceiveMsg()
{
    QString receiveMsg = myListener->getReceiveMsg();
    ui->plainTextEdit->appendPlainText("[from "+ getLocalIP()+"] "+receiveMsg);
    qDebug() << "on_displayReceiveMsg";
}


/*--------------@brief：获取本地的IP地址-------------*/
QString Widget::getLocalIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol
            && address != QHostAddress::LocalHost
            && address.toString().startsWith("192.168."))
        {
            return address.toString();
        }
    }
    return "";
}


/*--------------@brief：在'QPlainTextEdit'里显示消息-------------*/
void Widget::DisplayMsgInTextEdit()
{
    /*MyUdpMultiCastListener mMudpMultiCastListener;
    //组播加入成功做以下工作
    if(mMudpMultiCastListener.getOnConnect_Flag())
    {
        qDebug()<<"mMudpMultiCastListener.OnConnect_Flag"<<mMudpMultiCastListener.OnConnect_Flag;
        mMudpMultiCastListener.OnConnect_Flag = 0;
        ui->plainTextEdit->appendPlainText("**加入组播成功");
        ui->plainTextEdit->appendPlainText("**组播IP："+ui->MulticastAdd->text());
        ui->plainTextEdit->appendPlainText("**绑定端口："+ui->MulticastPort->text());
    }
    //Widget::Sleep(1);

    /*else
    {
        //ui->plainTextEdit->appendPlainText("**加入组播失败");
    }*/

    //数据发送成功加入成功做以下工作
    /*if(mMudpMultiCastListener.getOnSend_Flag())
    {
        qDebug()<<"mMudpMultiCastListener.OnSend_Flag"<<mMudpMultiCastListener.OnSend_Flag;
        mMudpMultiCastListener.OnSend_Flag = 0;
        ui->plainTextEdit->appendPlainText("[mulicast]"+ui->ProtocolCmd->text());
    }*/
}




















