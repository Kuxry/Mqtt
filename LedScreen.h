#pragma once
#include "txrMqttClient.h"
#include <string>

// LED屏幕控制类
class LedScreen
{
public:
    // 通过 `barcode` 识别不同的 LED 屏幕
    LedScreen(const std::string& barcode);
    ~LedScreen();

    // 连接MQTT服务器
    bool connect(const std::string& host, int port);

    // 断开连接
    void disconnect();

    // 发送LED控制命令
    void sendCommand(int messageId);

    // 播放指定内容（LED 显示 + 语音播报）
    void playContent(int messageId);

    // 进行语音播报
    void playVoice(const std::string& text);

private:
    txrMqttClient* m_client;
    std::string m_barcode;  // 设备唯一编号
    int m_messageSequence;  // 递增的消息序列号

    // 获取递增的 messageSequence
    int generateMessageSequence();
};

// 消息头部定义（符合 `BXmqtt-Y` 协议）
#define MQTT_MAGIC "BXPP"            // 协议标识
#define MQTT_CONTROLLER_TYPE "0x0a32" // 设备型号
#define MQTT_PROTOCOL_VERSION "0.0.4" // 协议版本号

// 消息ID定义
#define VTK_MSG_0 (0)
#define VTK_MSG_1 (1)
#define VTK_MSG_2 (2)
#define VTK_MSG_3 (3)
#define VTK_MSG_4 (4)
#define VTK_MSG_5 (5)
#define VTK_MSG_6 (6)
