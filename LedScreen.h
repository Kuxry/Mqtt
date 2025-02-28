#pragma once
#include "txrMqttClient.h"

// LED屏幕接口封装
class LedScreen
{
public:
    LedScreen();
    ~LedScreen();

    // 连接到MQTT服务苼E
    bool connect(const std::string& host, int port);

    // 断开连接
    void disconnect();

    // 发送脕E絃ED屏幕
    void sendCommand(int messageId);

    // 播放文字和觼E裟谌�
    void playContent(int messageId);

private:
    txrMqttClient* m_client;
};

// 消息ID定襾E
#define VTK_MSG_0 (0) // Info: 莵E中囱拱磁ィ蛘呤褂迷ぴ级丒新掏丒庠ぴ迹甘镜瞥Ａ帘驹ぴ汲晒Α�
#define VTK_MSG_1 (1) // Info: 预约成功
#define VTK_MSG_2 (2) // Info: 预约失败，莵E院笤偈浴�
#define VTK_MSG_3 (3) // Info: 预约成功，莵E谔Ц撕笤人俳丒丒馇颉Ｈ缧枞∠ぴ迹丒中囱拱磁ィ蛘呤褂萌∠丒∠ぴ迹甘镜粕了副救∠晒Α�
#define VTK_MSG_4 (4) // Info: 取消成功
#define VTK_MSG_5 (5) // Info: 取消失败，莵E院笤偈浴�
#define VTK_MSG_6 (6) // Info: 前方正在进行绿通紒E猓蠓匠盗厩丒鸶到丒丒馇颍丒诘却却�

