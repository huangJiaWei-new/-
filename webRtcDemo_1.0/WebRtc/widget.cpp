#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    getDeviceList();
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onCaptureTimeout()));
}

Widget::~Widget()
{
    delete ui;
}


/*--------------@brief：获取视频设备列表-------------*/
/*--------------@note： -------------*/
void Widget::getDeviceList()
{

    webrtc::VideoCaptureModule::DeviceInfo *info =
    webrtc::VideoCaptureFactory::CreateDeviceInfo(); //'info'用于访问WebRTC的视频捕获设备信息
    int deviceNum=info->NumberOfDevices(); //获取当前计算机上可用的视频捕获设备的数量

    //遍历可用的视频捕获设备
    for (int i = 0; i < deviceNum; ++i)
    {
        const uint32_t kSize = 256;
        char name[kSize] = {0};
        char id[kSize] = {0};

        //获取第 i 个设备的名称和ID
        if(info->GetDeviceName(i, name, kSize, id, kSize) != -1)
        {
            ui->comboBox->addItem(QString(name));
        }
    }

    if(deviceNum==0)
    {
        ui->open->setEnabled(false);
    }
}


/*--------------@brief：处理点击事件，打开或关闭摄像头-------------*/
/*--------------@note： -------------*/
void Widget::on_open_clicked()
{
    static bool flag=true;

    if(flag)
    {
        webrtc::VideoCaptureModule::DeviceInfo *device_info_ =
        webrtc::VideoCaptureFactory::CreateDeviceInfo();

        char device_name[256]; //用于存储设备名称和ID
        char unique_name[256];

        //获取用户选择的视频捕获设备的名称和唯一名称（ID）
        if(device_info_->GetDeviceName(ui->comboBox->currentIndex(), device_name, 256,
                                       unique_name, 256) !=0)
        {
            qDebug()<<"此设备获取失败";
            return ;
        }

        //创建一个视频捕获模块对象，该对象将用于打开和管理用户选择的视频捕获设备。
        m_module = webrtc::VideoCaptureFactory::Create(unique_name);
        if (m_module.get() == NULL)
        {
            qDebug()<<"webrtc::VideoCaptureFactory::创建失败";
            return ;
        }

        //将视频捕获模块的数据回调与 m_captureObserver 关联，以处理捕获的视频数据
        m_module->RegisterCaptureDataCallback(&m_captureObserver);
        //获取当前设备的捕获能力信息，并将其存储在 m_capability 中，以便后续使用
        device_info_->GetCapability(m_module->CurrentDeviceName(), 0, m_capability);

        //开始捕捉
        if(m_module->StartCapture(m_capability)!=0)
        {
            qDebug()<<"设备捕获启动失败";
            return;
        }

        if(m_module->CaptureStarted())
        {
            qDebug()<<"设备捕获正在运行";
        }

        m_timer.start(40);
        ui->open->setText(tr("关闭"));
    }
    else
    {
        ui->open->setText(tr("打开"));
        m_timer.stop();
        //重复连接会报错，需要先断开，才能再次连接
        m_module->StopCapture();
        if(!m_module->CaptureStarted())
        {
            qDebug()<<"设备捕获停止运行";
        }
        ui->video->clear();
    }
    flag=!flag;
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
void Widget::onCaptureTimeout()
{
    //在 QLabel 控件上显示图像
    ui->video->setPixmap(QPixmap::fromImage(m_captureObserver.m_lastImage));
}

