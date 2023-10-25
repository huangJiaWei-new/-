#ifndef WIDGET_H
#define WIDGET_H

#include "captureobserver.h"

#include <QWidget>
#include <QTimer>

#include "third_party/libyuv/include/libyuv/convert_argb.h"
#include "memory.h"
#include "api/scoped_refptr.h"
#include "api/video/i420_buffer.h"
#include "api/video/video_frame.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"
#include "modules/video_capture/video_capture_factory.h"
#include "rtc_base/synchronization/mutex.h"
#include "rtc_base/time_utils.h"
#include "system_wrappers/include/sleep.h"

#pragma execution_character_set("utf-8") //防止中文乱码

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/*--------------@brief：widget界面类-------------*/
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void getDeviceList();

private slots:
    void on_open_clicked();
    void onCaptureTimeout();

private:
    Ui::Widget *ui;
    QTimer m_timer;

    rtc::scoped_refptr<webrtc::VideoCaptureModule> m_module;
    CaptureObserver m_captureObserver;
    webrtc::VideoCaptureCapability m_capability;
};







#endif // WIDGET_H
