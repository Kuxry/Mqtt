#include "pch.h"
#include "QrCodeScanner.h"

QrCodeScanner::QrCodeScanner()
{
    m_client = new txrMqttClient();
}

QrCodeScanner::~QrCodeScanner()
{
    if (m_client)
    {
        delete m_client;
        m_client = nullptr;
    }
}

bool QrCodeScanner::connect(const std::string& host, int port)
{
    if (!m_client->connect(host, port))
    {
        std::cout << "connect to mqtt broker fail!" << std::endl;
        return false;
    }
    
    return true;
}

void QrCodeScanner::disconnect()
{
    m_client->disconnect();
}

void QrCodeScanner::subscribe(const std::string& topic)
{
    m_client->subscribe(topic);
    m_topic = topic;
}

std::string QrCodeScanner::getQrCodeInfo()
{
    mqtt::const_message_ptr msgPtr = m_client->getSubcribeMessage();
    if (msgPtr == nullptr)
    {
        return std::string();
    }

    const mqtt::string& topic = msgPtr->get_topic();
    if (topic == m_topic)
    {
        return msgPtr->get_payload_str();      
    }
    else
    {
        return std::string();
    }
   
}
