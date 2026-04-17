# ⚡ Voice-Enabled IoT Smart Switchboard (ESP32)

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/Platform-ESP32-orange.svg)
![Language](https://img.shields.io/badge/Language-C++-green.svg)

A professional IoT-based Home Automation system built with **ESP32** that allows users to control home appliances (Lights, Fans, etc.) via a **Premium Dark-Theme Web Dashboard** and **AI Voice Commands**.

---

## 🚀 Features

- **Dual-Mode Connectivity**: Operates in both AP (Access Point) and STA (Station) modes.
- **AI Voice Control**: Integrated Web Speech API for controlling appliances with English voice commands.
- **Smart WiFi Manager**: Real-time WiFi scanning and connection dashboard (No hardcoded credentials).
- **Responsive UI**: High-end dark theme dashboard built with HTML5/CSS3.
- **Active Low Relay Logic**: Optimized for standard relay modules to ensure safety during boot-up.
- **Asynchronous Communication**: Uses Fetch API for lag-free switching experience.

---

## 🛠️ Hardware Requirements

| Component | Specification |
| :--- | :--- |
| **Microcontroller** | ESP32 Development Board |
| **Relay Module** | 2-Channel Relay (Active Low) |
| **Connectivity** | WiFi 2.4GHz |
| **GPIO 26** | Connected to Relay 1 (Light) |
| **GPIO 27** | Connected to Relay 2 (Fan) |

---

## 💻 Installation & Setup

1. **Clone the Repository**:
   ```bash
   git clone [https://github.com/Gautam20040531/Smart-Home-Switchboard.git](https://github.com/Gautam20040531/Smart-Home-Switchboard.git)

 2.   Open in Arduino IDE:

Install ESP32 Board Core.

Select ESP32 Dev Module.

3. Upload the Sketch:

Connect your ESP32 via USB and click Upload.

4. Connect to WiFi:

Connect your smartphone to WiFi: Home_Automation_ESP32.

Password: 12345678

Open browser and navigate to 192.168.4.1.

🎤 Voice Commands
Once connected to the dashboard, tap the microphone icon and say:

"Turn on Light" / "Turn off Light"

"Turn on Fan" / "Turn off Fan"

📜 Project Documentation
The repository also includes a detailed professional documentation file: Voice-Enabled IoT Smart Switchboard.docx.

👨‍💻 Developed By
Gautam Pal Full-Stack Web Developer & IoT Enthusiast