#include "pch.h"
#include "LedScreen.h"
#include <nlohmann/json.hpp>

LedScreen::LedScreen()
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
    // 根据messageId选择要播放的内容
    std::string text;

    switch (messageId) {
        case VTK_MSG_0:
            text = "请持续按压按钮，或者使用预约二维码进行绿通检测预约，指示灯常亮表示预约成功。";
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

    // 构建JSON对象
    nlohmann::json jsonData;
    jsonData["name"] = "displayMessage";
    jsonData["input"]["text"] = text;

    // 将JSON对象转换为字符串
    std::string message = jsonData.dump();

    // 发送JSON命令
    std::string topic = "ledscreen/command";
    try {
        m_client->publish(topic, message);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to send JSON command: " << e.what() << std::endl;
    }
}


