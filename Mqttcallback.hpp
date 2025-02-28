#pragma once
#include "mqtt\async_client.h"

//mqtt�첽��Ϣ�ص���
class Mqttcallback :public virtual mqtt::callback
{
public:
    void message_arrived(mqtt::const_message_ptr msg) override
    {
        std::cout << "received message on topic:" << msg->get_topic() << std::endl;
        std::cout << "received message on content:" << msg->get_payload_str() << std::endl;
        m_recvedSubMsgQueue.push(msg);
    }

public:
    std::queue<mqtt::const_message_ptr> m_recvedSubMsgQueue; //���յ��Ķ�����Ϣ����

};