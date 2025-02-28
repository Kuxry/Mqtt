#include "pch.h"
#include "txrMqttClient.h"


txrMqttClient::txrMqttClient()
	:m_pClient(nullptr), 
	m_keepAlive(20), 
	m_pCallback(nullptr)
{
}

txrMqttClient::~txrMqttClient()
{
}

bool txrMqttClient::connect(const std::string& host, int port)
{
	if (m_pClient)
	{
		return true;
	}

	char uri[64] = { 0 };
	sprintf_s(uri,sizeof(uri),"tcp://%s:%d",host.c_str(),port);
	m_pClient = new mqtt::async_client(uri);
	// ﾉ靹ﾃﾁｬｽﾓﾑ｡ﾏ釤ｬｰ・ｨｱ｣ｳﾖﾁｬｽﾓｵﾄﾐﾄﾌ荳ﾍﾇ蠡暙ﾉｻ盻ｰ
	auto connOpts = mqtt::connect_options_builder()
		.keep_alive_interval(std::chrono::seconds(m_keepAlive)) // ﾐﾄﾌ荳・
		.clean_session(true) // ｿｪﾆ蠡暙ﾉｻ盻ｰﾑ｡ﾏ・
		.finalize(); // ﾍ・ﾉｹｹｽｨﾑ｡ﾏ・

	// ｳ｢ﾊﾔﾁｬｽﾓｵｽ MQTT ｴ惕・
	try {
		m_pClient->connect(connOpts)->wait();
	}
	catch (const mqtt::exception& exc) {
		// ﾈ郢軏ｶｻｽ MQTT ﾒ・｣｣ｬﾔ｡ｴ﨔ﾅﾏ｢ｲ｢ｷｵｻﾘｴ﨔惲・
		std::cerr << exc.what() << std::endl;
		return false;
	}

	return true;
}

void txrMqttClient::disconnect()
{
	// ｶﾏｿｪﾓ・MQTT ｴ惕昉ﾄﾁｬｽﾓ
	if (m_pClient)
	{
		m_pClient->disconnect()->wait();
		delete m_pClient;
		m_pClient = nullptr;
	}
	
}

void txrMqttClient::subscribe(const std::string& topic)
{
	m_pCallback = new Mqttcallback();
	m_pClient->set_callback(*m_pCallback);

	try {
		// ｶｩﾔﾄﾖ筌ｬQoS ﾉ靹ﾃﾎｪ 1｣ｨﾖﾁﾉﾙﾒｻｴﾎｴｫｵﾝ｣ｩ
		m_pClient->subscribe(topic, 1)->wait();
	}
	catch (const mqtt::exception& exc) {
		// ﾈ郢軏ｶｻｽ MQTT ﾒ・｣｣ｬﾔ｡ｴ﨔ﾅﾏ｢ｲ｢ｷｵｻﾘｴ﨔惲・
		std::cerr << exc.what() << std::endl;
	}
}

mqtt::const_message_ptr txrMqttClient::getSubcribeMessage()
{
	if (m_pCallback->m_recvedSubMsgQueue.empty())
	{
		return nullptr;
	}

	mqtt::const_message_ptr msgPtr = m_pCallback->m_recvedSubMsgQueue.front();
	m_pCallback->m_recvedSubMsgQueue.pop();
	return msgPtr;
}

void txrMqttClient::publish(const std::string& topic, const std::string& message)
{
	try {
		//ｷ｢ｲｼﾖ・
		mqtt::message_ptr pubmsg = mqtt::make_message(topic,message);
		const int QOS = 1;
		pubmsg->set_qos(QOS);
		const auto TIMEOUT = std::chrono::seconds(10);
		m_pClient->publish(pubmsg)->wait_for(TIMEOUT);

	}
	catch (const mqtt::exception& exc) {
		// ﾈ郢軏ｶｻｽ MQTT ﾒ・｣｣ｬﾔ｡ｴ﨔ﾅﾏ｢ｲ｢ｷｵｻﾘｴ﨔惲・
		std::cerr << exc.what() << std::endl;
	}
}
