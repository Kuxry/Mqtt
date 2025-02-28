#pragma once
#include "txrMqttClient.h"

// LEDÆÁÄ»½Ó¿Ú·â×°
class LedScreen
{
public:
    LedScreen();
    ~LedScreen();

    // Á¬½Óµ½MQTT·şÎñÆE
    bool connect(const std::string& host, int port);

    // ¶Ï¿ªÁ¬½Ó
    void disconnect();

    // ·¢ËÍÃEûÑ½LEDÆÁÄ»
    void sendCommand(int messageId);

    // ²¥·ÅÎÄ×ÖºÍÓEôÄÚÈİ
    void playContent(int messageId);

private:
    txrMqttClient* m_client;
};

// ÏûÏ¢ID¶¨ÒE
#define VTK_MSG_0 (0) // Info: ÇEÖĞø°´Ñ¹°´Å¥£¬»òÕßÊ¹ÓÃÔ¤Ô¼¶şÎ¬ÂEøĞĞÂÌÍ¨¼EâÔ¤Ô¼£¬Ö¸Ê¾µÆ³£ÁÁ±úæ¾Ô¤Ô¼³É¹¦¡£
#define VTK_MSG_1 (1) // Info: Ô¤Ô¼³É¹¦
#define VTK_MSG_2 (2) // Info: Ô¤Ô¼Ê§°Ü£¬ÇEÔºóÔÙÊÔ¡£
#define VTK_MSG_3 (3) // Info: Ô¤Ô¼³É¹¦£¬ÇEÚÌ§¸ËºóÔÈËÙ½øÈEEâÇøÓò¡£ÈçĞèÈ¡ÏûÔ¤Ô¼£¬ÇEÖĞø°´Ñ¹°´Å¥£¬»òÕßÊ¹ÓÃÈ¡Ïû¶şÎ¬ÂE¡ÏûÔ¤Ô¼£¬Ö¸Ê¾µÆÉÁË¸±úæ¾È¡Ïû³É¹¦¡£
#define VTK_MSG_4 (4) // Info: È¡Ïû³É¹¦
#define VTK_MSG_5 (5) // Info: È¡ÏûÊ§°Ü£¬ÇEÔºóÔÙÊÔ¡£
#define VTK_MSG_6 (6) // Info: Ç°·½ÕıÔÚ½øĞĞÂÌÍ¨¼Eâ£¬ºó·½³µÁ¾ÇEğ¸ú³µ½øÈEEâÇøÓò£¬ÇEÚµÈ´ıÇøµÈ´ı¡£

