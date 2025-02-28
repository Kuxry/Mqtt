#pragma once
#include "mqtt\async_client.h"

//mqtt异步消息回调类
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
    std::queue<mqtt::const_message_ptr> m_recvedSubMsgQueue; //接收到的订阅消息队列

};