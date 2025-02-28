#include "pch.h"
#include "LedScreen.h"

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
