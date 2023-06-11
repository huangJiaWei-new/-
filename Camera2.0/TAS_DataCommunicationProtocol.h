#ifndef TAS_DATACOMMUNICATIONPROTOCOL_H
#define TAS_DATACOMMUNICATIONPROTOCOL_H
#include <QObject>
/* 跟瞄系统数据通信协议 */
/**
 * @brief 主机发送TAS(跟瞄系统)的命令
 */
#define CMD_REQ_LINK  			0x01  //CsManager端测试是否连接成功
#define CMD_REQ_RUN  			0x02  //要求TAS端开始运行
#define CMD_REQ_STOP  			0x03  //要求TAS端停止运行
#define CMD_REQ_FIRE 			0x04  //设置跟瞄系统是否开火
#define CMD_REQ_SET_AUTO  		0x05  //设置是否自动跟踪和瞄准，0手动，1自动
#define CMD_REQ_GET_AUTO		0x06  //读取设置的自动或者手动模式
#define CMD_REQ_SET_TRACK		0x07  //设置由远程控制手动跟踪的控制值
#define CMD_REQ_GET_TRACK  		0x08  //获取TAS端跟踪信息，该指令可以自动发送
#define CMD_REQ_SET_VIDEO		0x09  //设置开始跟踪结果的视频传输参数
#define CMD_REQ_SET_PARA		0x0A  //设置跟瞄系统参数
#define CMD_REQ_GET_PARA		0x0B  //读取跟瞄系统参数

/**
 * @brief 由TAS(跟瞄系统)收到主机命令后或者主动发送的命令
 */
#define CMD_RSP_LINK  			0x81  //PC端测试连接
#define CMD_RSP_RUN				0x82  //返回已经运行
#define CMD_RSP_STOP			0x83  //返回停止运行
#define CMD_RSP_FIRED 			0x84  //返回已经开火
#define CMD_RSP_AUTO  			0x86  //返回车辆是否自动控制
#define CMD_RSP_TRACK			0x88  //返回跟踪设定值
#define CMD_RSP_VIDEO 			0X89  //返回传输视频设置值
#define CMD_RSP_PARA			0x8B  //返回设置的跟瞄系统参数
#define CMD_RSP_VIDEO_STREAM	0x8C  //输出H264码流

/**
 * @brief 3.1.6_摄像头跟踪信息
 */
typedef struct
{
    uint8_t mode; //控制模式，0为相对模式，后面的数据是相对应当前值移动的角度
                  //1位绝对模式，后面的数据为相对于中心位置的绝对度数
    float yaw;    //水平，度数，最大360度
    float pich;   //俯仰，度数，最大90度
    uint16_t pointx; //跟踪框左上角位置X
    uint16_t pointy; //跟踪框左上角位置Y
    uint16_t width;	 //跟踪框宽度
    uint16_t height; //跟踪框高度
}pk_track_t;

/**
 * @brief 3.1.7_视频回传命令
 */
typedef struct
{
    uint8_t mode;   //0为回传原始数据，1为回传带跟踪框的数据
    uint8_t format; //0不输出视频，1：H264码流，2：mpeg:3：YUV:4：RGB图像
    uint16_t fbs;   // 每秒传输多少帧

}pk_video_t;

/**
 * @brief 3.1.9_摄像头工作参数
 */
typedef struct
{
    uint8_t devid;     //设备的ID号
    uint8_t addr;      //转台的Modbus控制地址
    uint16_t baudrate; //转台RS485通信波特率，该值需X100，如115200，值为1152
    uint16_t width;    //摄像头的图像的宽度
    uint16_t height;   //摄像头的图像的高度
    uint8_t mode;      //0为回传原始数据，1为回传带跟踪框的数据
    uint8_t format;    //0位H264码流，1位mpeg，2位YUV，3位RGB
    uint16_t fbs;      // 每秒传输多少帧
}pk_para_t;

/**
 * @brief 发送命令对应的消息包头
 */
typedef struct
{
    uint8_t  cmd;	 //通信用的命令
    uint8_t  id;	 //跟瞄设备编号，一般设置为0x01
    uint16_t length; //跟瞄通信数据长度
}pk_head_t;

/**
 * @brief 对应命令的数据结构体
 */
typedef struct
{
    pk_head_t  pkhead;
    pk_track_t pktrack;
    pk_video_t pkvideo;
    pk_para_t  pkpara;
}command;

#endif // TAS_DATACOMMUNICATIONPROTOCOL_H
