#pragma once
#include "mqtt\async_client.h"
#include "Mqttcallback.hpp"

//mqttЭ��ӿڷ�װ
class txrMqttClient
{
public:
	txrMqttClient();
	~txrMqttClient();

public:
	//���ӵ�mqtt����
	bool connect(const std::string& host,int port);

	//�Ͽ�����
	void disconnect();

	//����������Ϣ
	void subscribe(const std::string& topic);

	//��ȡ������Ϣ����Ҫ��ѭ���е��ö��
	mqtt::const_message_ptr getSubcribeMessage();

	//����������Ϣ
	void publish(const std::string& topic, const std::string& message);

private:
	mqtt::async_client* m_pClient;
	int m_keepAlive; //�����������λ��
	Mqttcallback* m_pCallback; //���ն�����Ϣ�Ļص�����

};

