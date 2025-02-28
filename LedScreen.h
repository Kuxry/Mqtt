#pragma once
#include "txrMqttClient.h"

// LED��Ļ�ӿڷ�װ
class LedScreen
{
public:
    LedScreen();
    ~LedScreen();

    // ���ӵ�MQTT������
    bool connect(const std::string& host, int port);

    // �Ͽ�����
    void disconnect();

    // �������LED��Ļ
    void sendCommand(int messageId);

private:
    txrMqttClient* m_client;
};

// ��ϢID����
#define VTK_MSG_0 (0) // Info: �������ѹ��ť������ʹ��ԤԼ��ά�������ͨ���ԤԼ��ָʾ�Ƴ�����ʾԤԼ�ɹ���
#define VTK_MSG_1 (1) // Info: ԤԼ�ɹ�
#define VTK_MSG_2 (2) // Info: ԤԼʧ�ܣ����Ժ����ԡ�
#define VTK_MSG_3 (3) // Info: ԤԼ�ɹ�������̧�˺����ٽ�������������ȡ��ԤԼ���������ѹ��ť������ʹ��ȡ����ά��ȡ��ԤԼ��ָʾ����˸��ʾȡ���ɹ���
#define VTK_MSG_4 (4) // Info: ȡ���ɹ�
#define VTK_MSG_5 (5) // Info: ȡ��ʧ�ܣ����Ժ����ԡ�
#define VTK_MSG_6 (6) // Info: ǰ�����ڽ�����ͨ��⣬�󷽳�����������������������ڵȴ����ȴ���

