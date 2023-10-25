#ifndef CAPTUREOBSERVER_H
#define CAPTUREOBSERVER_H

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

#include <QImage>

class CaptureObserver : public rtc::VideoSinkInterface<webrtc::VideoFrame>
{
public:
    CaptureObserver();
    void OnFrame(const webrtc::VideoFrame& videoFrame) override; //处理接收到的帧

public:
    QImage m_lastImage;
    int incoming_frames_;
    webrtc::Mutex capture_lock_;
};



#endif // CAPTUREOBSERVER_H
