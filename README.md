# Project Overview

## Project Structure

This project consists of the following core components:

- **LedScreen**: Responsible for controlling the LED screen display and voice playback.
- **txrMqttClient**: Encapsulates the MQTT client's connection, subscription, and publishing functionalities.
- **Mqttcallback**: Handles MQTT message callbacks.
- **QrCodeScanner**: Manages QR code scanning and related MQTT interactions.

## Main Features

### 1. LED Screen Control

- **Connect to MQTT Server**: Connect to the specified MQTT server using the `LedScreen::connect` method.
- **Send Control Commands**: Use the `LedScreen::sendCommand` method to send control commands to the LED screen.
- **Play Content**: The `LedScreen::playContent` method plays the corresponding content based on the message ID and sends display and voice commands via MQTT.

### 2. MQTT Client

- **Connect and Disconnect**: The `txrMqttClient` class provides methods to connect and disconnect from the MQTT server.
- **Subscribe and Publish**: Supports subscribing to specified topics and publishing messages to topics.

### 3. QR Code Scanning

- **Connect and Disconnect**: The `QrCodeScanner` class provides methods to connect and disconnect from the MQTT server.
- **Subscribe to QR Code Information**: Obtain QR code information by subscribing to topics.

## Logical Flow

1. **Initialization**:
   - Create `LedScreen` instances and identify different LED screens via `barcode`.
   - Create `txrMqttClient` instances for MQTT communication.

2. **Connect to MQTT Server**:
   - Use the `connect` method to connect to the MQTT server.

3. **Send and Receive Messages**:
   - Send control commands and play content using `sendCommand` and `playContent` methods.
   - Use `Mqttcallback` to handle received MQTT messages.

4. **Play Content**:
   - The `playContent` method selects the content to play based on the message ID and sends display and voice commands via MQTT.

5. **Disconnect**:
   - Use the `disconnect` method to disconnect from the MQTT server.

## Usage Example

```cpp
int main()
{
    // Create two LED screen instances (different barcodes)
    LedScreen ledScreen1("010001210901000134F75678"); // First screen
    LedScreen ledScreen2("010001210901000134F75679"); // Second screen

    // Connect to MQTT server
    ledScreen1.connect("192.168.1.100", 1883);
    ledScreen2.connect("192.168.1.100", 1883);

    // Play the same or different content
    ledScreen1.playContent(VTK_MSG_0);
    ledScreen2.playContent(VTK_MSG_3);

    return 0;
}
```

## Dependencies

- **nlohmann/json**: Used for constructing and parsing JSON objects.
- **MQTT Library**: Used for implementing MQTT protocol communication.

## Notes

- Ensure the MQTT server address and port are correct.
- Ensure the `nlohmann/json` library is correctly installed and linked.
