#pragma once
#include "txrMqttClient.h"

//��άE������ӿڷ�װ
class QrCodeScanner
{
public:
	QrCodeScanner();
	~QrCodeScanner();

public:
	//���ӵ�mqtt����
	bool connect(const std::string& host, int port);

	//�Ͽ�����
	void disconnect();

	//���Ķ�άE�Ϣ��́E
	void subscribe(const std::string& topic);
	
	//��ȡ��άE�Ϣ
	std::string getQrCodeInfo();

private:
	txrMqttClient* m_client;
	std::string m_topic;
};

