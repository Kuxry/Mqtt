#pragma once
#include "txrMqttClient.h"

//¶şÎ¬ÂE¨ÃèÆ÷½Ó¿Ú·â×°
class QrCodeScanner
{
public:
	QrCodeScanner();
	~QrCodeScanner();

public:
	//Á¬½Óµ½mqttÍø¹Ø
	bool connect(const std::string& host, int port);

	//¶Ï¿ªÁ¬½Ó
	void disconnect();

	//¶©ÔÄ¶şÎ¬ÂEûÏ¢Ö÷ÌE
	void subscribe(const std::string& topic);
	
	//»ñÈ¡¶şÎ¬ÂEÅÏ¢
	std::string getQrCodeInfo();

private:
	txrMqttClient* m_client;
	std::string m_topic;
};

