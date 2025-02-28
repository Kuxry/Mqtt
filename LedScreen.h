#pragma once
#include "txrMqttClient.h"

// LED��Ļ�ӿڷ�װ
class LedScreen
{
public:
    LedScreen();
    ~LedScreen();

    // ���ӵ�MQTT����ƁE
    bool connect(const std::string& host, int port);

    // �Ͽ�����
    void disconnect();

    // ����ÁE�ѽLED��Ļ
    void sendCommand(int messageId);

    // �������ֺ�ӁE�����
    void playContent(int messageId);

private:
    txrMqttClient* m_client;
};

// ��ϢID��ҁE
#define VTK_MSG_0 (0) // Info: ǁE�����ѹ��ť������ʹ��ԤԼ��άE�����ͨ��E�ԤԼ��ָʾ�Ƴ������ԤԼ�ɹ���
#define VTK_MSG_1 (1) // Info: ԤԼ�ɹ�
#define VTK_MSG_2 (2) // Info: ԤԼʧ�ܣ�ǁEԺ����ԡ�
#define VTK_MSG_3 (3) // Info: ԤԼ�ɹ���ǁE�̧�˺����ٽ�ȁE�E���������ȡ��ԤԼ��ǁE�����ѹ��ť������ʹ��ȡ����άE���ԤԼ��ָʾ����˸���ȡ���ɹ���
#define VTK_MSG_4 (4) // Info: ȡ���ɹ�
#define VTK_MSG_5 (5) // Info: ȡ��ʧ�ܣ�ǁEԺ����ԡ�
#define VTK_MSG_6 (6) // Info: ǰ�����ڽ�����ͨ��E⣬�󷽳���ǁE������ȁE�E�����ǁEڵȴ����ȴ���

