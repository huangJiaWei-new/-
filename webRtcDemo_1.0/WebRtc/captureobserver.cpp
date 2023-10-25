#include <QImage>
#include <QDebug>
#include <memory>
#include "captureobserver.h"


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
CaptureObserver::CaptureObserver()
   :incoming_frames_(0)
{

}


/*--------------@brief：视频捕获的回调函数-------------*/
/*--------------@note： 新的视频帧可用即被调用-------------*/
void CaptureObserver::OnFrame(const webrtc::VideoFrame &videoFrame)
{
    webrtc::MutexLock lock(&capture_lock_); //使用互斥锁保证处理视频帧数据时不会被多线程干扰
    int height = videoFrame.height();
    int width = videoFrame.width();

    incoming_frames_++; //接收到的帧的计数

    //qDebug()<<"width"<<width<<"height"<<height<<"incoming_frames_"<<incoming_frames_;

    //将收到的数据帧转换下格式
    rtc::scoped_refptr<webrtc::I420BufferInterface> buffer(
                 videoFrame.video_frame_buffer()->ToI420());

    //开辟一段存放BGR数据的空间
    const int length =buffer->width()* buffer->height()*3;
    //qDebug()<<"buffer->width()"<<buffer->width()<<"buffer->height()"<<buffer->height();
    uchar *imageBuffer=new uchar[length];

    //使用libyuvy库转换一帧数据到BGR
    libyuv::I420ToRGB24(buffer->DataY(), buffer->StrideY(), buffer->DataU(),
                       buffer->StrideU(), buffer->DataV(), buffer->StrideV(),
                       imageBuffer,
                       buffer->width()*3,
                       buffer->width(), buffer->height());
    //将得到的数据放入QImage中
    QImage image(imageBuffer,buffer->width(), buffer->height(), QImage::Format_BGR888);
    //qDebug()<<image;
    m_lastImage=image.copy();
    delete imageBuffer;
}

