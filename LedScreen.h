#pragma once
#include "txrMqttClient.h"

// LED屏幕接口封装
class LedScreen
{
public:
    LedScreen();
    ~LedScreen();

    // 连接到MQTT服务器
    bool connect(const std::string& host, int port);

    // 断开连接
    void disconnect();

    // 发送命令到LED屏幕
    void sendCommand(int messageId);

private:
    txrMqttClient* m_client;
};

// 消息ID定义
#define VTK_MSG_0 (0) // Info: 请持续按压按钮，或者使用预约二维码进行绿通检测预约，指示灯常亮表示预约成功。
#define VTK_MSG_1 (1) // Info: 预约成功
#define VTK_MSG_2 (2) // Info: 预约失败，请稍后再试。
#define VTK_MSG_3 (3) // Info: 预约成功，请在抬杆后匀速进入检测区域。如需取消预约，请持续按压按钮，或者使用取消二维码取消预约，指示灯闪烁表示取消成功。
#define VTK_MSG_4 (4) // Info: 取消成功
#define VTK_MSG_5 (5) // Info: 取消失败，请稍后再试。
#define VTK_MSG_6 (6) // Info: 前方正在进行绿通检测，后方车辆请勿跟车进入检测区域，请在等待区等待。

