#include <iostream>
#include <vector>
#include <windows.h>

// 串口设备名
const std::string SERIAL_PORT = "COM3";

// 计算校验码
uint8_t calculateChecksum(const std::vector<uint8_t>& data) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        checksum ^= data[i];
    }
    return checksum;
}

// 发送数据
bool sendData(HANDLE hSerial, const std::vector<uint8_t>& command) {
    DWORD bytesWritten;
    return WriteFile(hSerial, command.data(), static_cast<DWORD>(command.size()), &bytesWritten, NULL);
}

// 读取数据
std::vector<uint8_t> receiveData(HANDLE hSerial) {
    std::vector<uint8_t> response(256); // 扫码数据一般不会太长
    DWORD bytesRead;
    ReadFile(hSerial, response.data(), static_cast<DWORD>(response.size()), &bytesRead, NULL);
    response.resize(bytesRead);
    return response;
}

// 打开串口
HANDLE openSerialPort(const std::string& portName) {
    HANDLE hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "无法打开串口 " << portName << std::endl;
        return INVALID_HANDLE_VALUE;
    }

    // 配置串口
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "获取串口状态失败" << std::endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    dcbSerialParams.BaudRate = CBR_115200; // 根据扫码器说明书设置波特率
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "无法配置串口" << std::endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    return hSerial;
}

// 字节流转换为 UTF-8 字符串
std::string bytesToUtf8(const std::vector<uint8_t>& data) {
    if (data.empty()) return "";

    // 假设扫码器返回 GBK 编码，转换为 UTF-8
    int wideSize = MultiByteToWideChar(936, 0, (char*)data.data(), (int)data.size(), NULL, 0);
    std::wstring wideStr(wideSize, 0);
    MultiByteToWideChar(936, 0, (char*)data.data(), (int)data.size(), &wideStr[0], wideSize);

    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string utf8Str(utf8Size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Size, NULL, NULL);

    return utf8Str;
}

// 获取扫码结果（0x30 指令）
std::string getScanResult(HANDLE hSerial) {
    std::vector<uint8_t> command = { 0x55, 0xAA, 0x30, 0x00, 0x00 };
    command.push_back(calculateChecksum(command));

    sendData(hSerial, command);
    std::vector<uint8_t> response = receiveData(hSerial);

    if (response.size() < 7) {
        std::cerr << "扫码器未返回有效数据" << std::endl;
        return "";
    }

    // 解析扫码数据
    std::vector<uint8_t> scanData(response.begin() + 6, response.end() - 1); // 去掉协议头
    return bytesToUtf8(scanData);
}


// 设置扫码器结果上报模式 (0x31)
bool setReportMode(HANDLE hSerial, uint8_t mode, uint8_t timeout = 0) {
    std::vector<uint8_t> command = { 0x55, 0xAA, 0x31, 0x02, 0x00, mode, timeout };
    command.push_back(calculateChecksum(command));
    return sendData(hSerial, command);
}


// 获取扫码结果（区分数据来源，0x33）
std::pair<uint8_t, std::string> getScanResultWithSource(HANDLE hSerial) {
    std::vector<uint8_t> command = { 0x55, 0xAA, 0x33, 0x00, 0x00 };
    command.push_back(calculateChecksum(command));

    sendData(hSerial, command);
    std::vector<uint8_t> response = receiveData(hSerial);

    if (response.size() < 8) {
        std::cerr << "扫码器未返回有效数据" << std::endl;
        return { 0, "" };
    }

    uint8_t sourceType = response[6];
    std::vector<uint8_t> scanData(response.begin() + 7, response.end() - 1);
    return { sourceType, std::string(scanData.begin(), scanData.end()) };
}

// 获取按键值 (0x32)
uint8_t getKeyPress(HANDLE hSerial) {
    std::vector<uint8_t> command = { 0x55, 0xAA, 0x32, 0x00, 0x00 };
    command.push_back(calculateChecksum(command));

    sendData(hSerial, command);
    std::vector<uint8_t> response = receiveData(hSerial);


    if (response.size() < 7) {
        std::cerr << "data no vail" << std::endl;
        return 0;
    }

    return response[6]; // 返回按键值
}

// 主函数
int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台编码为 UTF-8
    HANDLE hSerial = openSerialPort(SERIAL_PORT);
    if (hSerial == INVALID_HANDLE_VALUE) return -1;

    std::string scanData = getScanResult(hSerial);
    if (!scanData.empty()) {
        std::cout << "扫码结果: " << scanData << std::endl;
    }
    else {
        std::cerr << "未获取到二维码数据" << std::endl;
    }

    CloseHandle(hSerial);
    return 0;
}
