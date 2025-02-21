#include <iostream>
#include <vector>
#include <windows.h>

// 串口设备名（Windows 下 COM 口，例如 COM3）
const std::string SERIAL_PORT = "COM3";

// **计算校验码**
uint8_t calculateChecksum(const std::vector<uint8_t>& data) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        checksum ^= data[i];
    }
    return checksum;
}

// **发送数据到扫码器**
bool sendData(HANDLE hSerial, const std::vector<uint8_t>& command) {
    DWORD bytesWritten;
    return WriteFile(hSerial, command.data(), static_cast<DWORD>(command.size()), &bytesWritten, NULL);
}

// **读取扫码器返回的数据**
std::vector<uint8_t> receiveData(HANDLE hSerial) {
    std::vector<uint8_t> response(64);
    DWORD bytesRead;
    ReadFile(hSerial, response.data(), static_cast<DWORD>(response.size()), &bytesRead, NULL);
    response.resize(bytesRead);
    return response;
}

// **打开串口**
HANDLE openSerialPort(const std::string& portName) {
    HANDLE hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "无法打开串口 " << portName << std::endl;
        return INVALID_HANDLE_VALUE;
    }
    return hSerial;
}


// **获取扫码结果（指令 0x30）**
std::string getScanResult(HANDLE hSerial) {
    // 构造 0x30 指令数据包
    std::vector<uint8_t> command = {0x55, 0xAA, 0x30, 0x00, 0x00};
    command.push_back(calculateChecksum(command)); // 添加校验字

    // 发送指令
    sendData(hSerial, command);

    // 读取扫码器返回数据
    std::vector<uint8_t> response = receiveData(hSerial);

    // 校验数据长度
    if (response.size() < 7) {
        std::cerr << "扫码器未返回有效数据" << std::endl;
        return "";
    }

    // 解析扫码数据
    uint8_t status = response[3]; // 标识字 0x00 代表成功
    if (status != 0x00) {
        std::cerr << "扫码器返回错误状态：" << static_cast<int>(status) << std::endl;
        return "";
    }

    // 提取扫码结果
    std::string qrContent(response.begin() + 7, response.end());
    std::cout << "扫码结果：" << qrContent << std::endl;

    return qrContent;
}
