# ⚡ ESP8266 Smart Switchboard with Web UI & Voice Control

## 📖 Overview
This project transforms a standard ESP8266 module into an advanced smart home automation controller. It features a responsive, dark-mode web interface that mimics physical switchboards, a built-in WiFi scanner/manager, and voice control capabilities to manage home appliances.

## ✨ Features
- **🌐 Standalone AP & Station Mode:** Hosts its own local network (`Home_Automation`) or connects to your existing home router.
- **📱 Responsive UI:** Beautiful, modern web interface built with HTML, CSS, and JavaScript. No app installation required!
- **🗣️ Voice Control:** Integrated Web Speech API allows you to control appliances using voice commands like *"Turn on light"* or *"Turn off fan"*.
- **📡 On-Board WiFi Manager:** Scan and connect to local networks directly from the web panel without hardcoding credentials.
- **🔌 2-Channel Relay Control:** Manages two separate appliances securely.

## 🛠️ Components Required
To build this project, you will need the following hardware:
1. **ESP8266 Development Board** (NodeMCU 1.0 or Wemos D1 Mini)
2. **2-Channel Relay Module (5V)** (Active-Low or Active-High)
3. **Jumper Wires** (Female-to-Female)
4. **5V Power Supply** (Micro USB cable or external power source)
5. Appliances to control (e.g., LED bulb, Fan)

## ⚡ Circuit Diagram & Pin Connections
Make the connections between the ESP8266 and the Relay Module as follows:

| ESP8266 Pin | Relay Module Pin | Description |
| :--- | :--- | :--- |
| **D1 (GPIO 5)** | **IN1** | Controls Relay 1 (Light) |
| **D2 (GPIO 4)** | **IN2** | Controls Relay 2 (Fan) |
| **VIN / 5V** | **VCC** | Provides 5V power to the relay |
| **GND** | **GND** | Common Ground |

## 🚀 Installation & Setup
1. Clone this repository or download the source code.
2. Open the `.ino` file in the [Arduino IDE](https://www.arduino.cc/en/software).
3. Go to **Tools > Board > Boards Manager** and install the `ESP8266` board package.
4. Connect your ESP8266 to your PC, select the correct Board and COM Port.
5. Click **Upload**.

## 💡 How to Use
1. **Power Up:** Once uploaded, power the ESP8266. It will create a WiFi hotspot named `Home_Automation`.
2. **Connect:** Connect your phone or PC to this WiFi network (No password required by default).
3. **Open Dashboard:** Open a web browser and navigate to `http://192.168.4.1`.
4. **Control Appliances:** Tap the toggle switches on the screen to turn the relays ON or OFF.
5. **Connect to Internet:** Scroll down and click **"Connect to Internet"** to scan for your home WiFi. Enter your password to connect the ESP8266 to your router.
6. **Voice Command:** Once connected to the internet, tap the **"Mic 🎤"** button and speak your command.

## ⚠️ Important Notes
- **Voice Control Permissions:** Voice control uses the browser's Web Speech API. Ensure you grant microphone permissions. Some mobile browsers may restrict microphone access over non-HTTPS IP addresses.
- **High Voltage Warning:** Please be extremely careful when connecting AC appliances (220V/110V) to the relay module. If you are not familiar with AC wiring, seek help from a professional electrician.
