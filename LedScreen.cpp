#include "pch.h"
#include "LedScreen.h"
#include <nlohmann/json.hpp>

LedScreen::LedScreen(const std::string& barcode)
    : m_barcode(barcode), m_messageSequence(0)
{
    m_client = new txrMqttClient();
}

LedScreen::~LedScreen()
{
    if (m_client)
    {
        disconnect();
        delete m_client;
        m_client = nullptr;
    }
}

bool LedScreen::connect(const std::string& host, int port)
{
    if (!m_client->connect(host, port))
    {
        std::cerr << "Failed to connect to MQTT broker!" << std::endl;
        return false;
    }
    return true;
}

void LedScreen::disconnect()
{
    if (m_client)
    {
        m_client->disconnect();
    }
}

void LedScreen::sendCommand(int messageId)
{
    std::string topic = "ledscreen/command";
    std::string message = std::to_string(messageId);

    try {
        m_client->publish(topic, message);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to send command: " << e.what() << std::endl;
    }
}

void LedScreen::playContent(int messageId)
{
    // 选择播放的内容
    std::string text;
    switch (messageId) {
    case VTK_MSG_0:
        text = "请持续按压按钮，或者使用预约二维码进行绿通检测预约，指示灯常亮表示预约成功";
        break;
    case VTK_MSG_1:
        text = "预约成功";
        break;
    case VTK_MSG_2:
        text = "预约失败，请稍后再试。";
        break;
    case VTK_MSG_3:
        text = "预约成功，请在抬杆后匀速进入检测区域。如需取消预约，请持续按压按钮，或者使用取消二维码取消预约，指示灯闪烁表示取消成功。";
        break;
    case VTK_MSG_4:
        text = "取消成功";
        break;
    case VTK_MSG_5:
        text = "取消失败，请稍后再试。";
        break;
    case VTK_MSG_6:
        text = "前方正在进行绿通检测，后方车辆请勿跟车进入检测区域，请在等待区等待。";
        break;
    default:
        text = "未知命令";
        break;
    }

    // 发送LED显示内容
    nlohmann::json payload;
    payload["name"] = "startPlay";
    payload["input"]["type"] = "program";
    payload["input"]["playlist"] = "/lists/play_" + std::to_string(messageId) + ".json"; // 设定播放列表
    payload["input"]["text"] = text;

    // 构建MQTT消息
    std::string mqttMessage = std::string(MQTT_MAGIC) + " " +
        MQTT_CONTROLLER_TYPE + " " +
        MQTT_PROTOCOL_VERSION + " " +
        m_barcode + " " +
        std::to_string(generateMessageSequence()) + "\n" +
        payload.dump();

    std::string topic = "ledscreen/command";

    try {
        m_client->publish(topic, mqttMessage);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to send JSON command: " << e.what() << std::endl;
    }

    // 语音播报
    playVoice(text);
}

void LedScreen::playVoice(const std::string& text)
{
    // 发送语音播报
    nlohmann::json payload;
    payload["name"] = "addVoice";
    payload["input"]["text"] = text;
    payload["input"]["gender"] = "0";  // 女声
    payload["input"]["speed"] = "50";  // 语速 50%
    payload["input"]["tone"] = "50";   // 语调 50%
    payload["input"]["volume"] = "50"; // 音量 50%
    payload["input"]["loop"] = "1";    // 播放 1 次

    std::string topic = "ledscreen/command";

    try {
        m_client->publish(topic, payload.dump());
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to send voice command: " << e.what() << std::endl;
    }
}

int LedScreen::generateMessageSequence()
{
    m_messageSequence = (m_messageSequence + 1) % 32768;
    return m_messageSequence;
}


int main()
{
    // 创建两个LED屏幕实例（不同的 barcode）
    LedScreen ledScreen1("010001210901000134F75678"); // 第一块屏幕
    LedScreen ledScreen2("010001210901000134F75679"); // 第二块屏幕

    // 连接MQTT服务器
    ledScreen1.connect("192.168.1.100", 1883);
    ledScreen2.connect("192.168.1.100", 1883);

    // 播放相同或不同的内容
    ledScreen1.playContent(VTK_MSG_0);
    ledScreen2.playContent(VTK_MSG_3);

    return 0;
}
