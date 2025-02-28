#pragma once
#include "mqtt\async_client.h"
#include "Mqttcallback.hpp"

//mqtt协议接口封装
class txrMqttClient
{
public:
	txrMqttClient();
	~txrMqttClient();

public:
	//连接到mqtt网关
	bool connect(const std::string& host,int port);

	//断开连接
	void disconnect();

	//订阅主题消息
	void subscribe(const std::string& topic);

	//获取主题消息，需要在循环中调用多次
	mqtt::const_message_ptr getSubcribeMessage();

	//发布主题消息
	void publish(const std::string& topic, const std::string& message);

private:
	mqtt::async_client* m_pClient;
	int m_keepAlive; //心跳间隔，单位秒
	Mqttcallback* m_pCallback; //接收订阅消息的回调函数

};

