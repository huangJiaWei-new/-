QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    captureobserver.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    captureobserver.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#----------------------------@note:WebRtc库----------------------------#
win32: LIBS += -L$$PWD/../../../WebRtc/webrtc/webrtc-new/src/out/Default_qt/obj/ -lwebrtc

INCLUDEPATH += $$PWD/../../../WebRtc/webrtc/webrtc-new/src/out/Default_qt/obj
DEPENDPATH += $$PWD/../../../WebRtc/webrtc/webrtc-new/src/out/Default_qt/obj

#----------------------------@note:WebRtc库文件----------------------------#
INCLUDEPATH += D:/WebRtc/webrtc/webrtc-new/src/third_party/abseil-cpp
DEPENDPATH += D:/WebRtc/webrtc/webrtc-new/src/third_party/abseil-cpp

INCLUDEPATH += D:/WebRtc/webrtc/webrtc-new/src
DEPENDPATH += D:/WebRtc/webrtc/webrtc-new/src

INCLUDEPATH += D:/WebRtc/webrtc/webrtc-new/src/third_party/libyuv/include
DEPENDPATH += D:/WebRtc/webrtc/webrtc-new/src/third_party/libyuv/include

#----------------------------@note:windows系统库----------------------------#
DEFINES += WEBRTC_WIN
LIBS += -lstrmiids -lOle32 -lOleAut32 -lwinmm -luser32

#解决运行时库的问题
CONFIG(debug, debug|release)
{
   QMAKE_CXXFLAGS_DEBUG += /MTd
}

CONFIG(release, debug|release)
{
   QMAKE_CXXFLAGS_RELEASE += /MT
}
