#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const int RELAY1_PIN = 26; // Light
const int RELAY2_PIN = 27; // Fan

const char* ap_ssid = "Home_Automation_ESP32";
const char* ap_password = "12345678"; 

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Smart Switchboard</title>
  <style>
    body { font-family: 'Segoe UI', sans-serif; background-color: #2c3e50; color: white; text-align: center; margin: 0; padding: 20px; }
    h2 { color: #ecf0f1; }
    .panel { background: #34495e; padding: 20px; border-radius: 15px; max-width: 400px; margin: 0 auto; box-shadow: 0px 10px 20px rgba(0,0,0,0.5); }
    .switch-container { display: flex; justify-content: space-between; align-items: center; background: #2c3e50; padding: 15px; margin: 15px 0; border-radius: 10px; border: 2px solid #1a252f; }
    .switch-label { font-size: 20px; font-weight: bold; }
    .switch-btn { width: 80px; height: 40px; border-radius: 20px; background: #555; position: relative; cursor: pointer; transition: 0.3s; box-shadow: inset 0px 3px 6px rgba(0,0,0,0.4); }
    .switch-btn::after { content: ''; position: absolute; width: 34px; height: 34px; background: #ccc; border-radius: 50%; top: 3px; left: 3px; transition: 0.3s; box-shadow: 0px 2px 5px rgba(0,0,0,0.5); }
    .active { background: #2ecc71; box-shadow: inset 0px 3px 6px rgba(0,0,0,0.2), 0px 0px 15px #2ecc71; }
    .active::after { left: 43px; background: white; }
    .action-btn { background: #3498db; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; margin-top: 15px; font-size: 16px; width: 100%; font-weight: bold; }
    .mic-btn { background: #e74c3c; border-radius: 50px; font-size: 20px; padding: 15px; margin-top: 20px; width: auto; box-shadow: 0px 4px 10px rgba(231,76,60,0.5); }
    #wifiSetup { display: none; background: #1a252f; padding: 15px; margin-top: 15px; border-radius: 10px; }
    select, input { width: 100%; padding: 10px; margin: 5px 0; border-radius: 5px; border: none; box-sizing: border-box; }
  </style>
</head>
<body>
  <div class="panel">
    <h2>⚡ ESP32 Smart Switch</h2>
    <div class="switch-container">
      <div class="switch-label">💡 Light</div>
      <div id="sw1" class="switch-btn" onclick="toggleRelay(1)"></div>
    </div>
    <div class="switch-container">
      <div class="switch-label">🌀 Fan</div>
      <div id="sw2" class="switch-btn" onclick="toggleRelay(2)"></div>
    </div>
    <button class="action-btn mic-btn" onclick="startVoice()">🎤 Tap to Speak</button>
    <p id="voiceLog" style="color:#bdc3c7; font-size:14px;">Say "Turn on light" or "Turn off fan"</p>
    <hr style="border-color:#2c3e50; margin: 20px 0;">
    <button class="action-btn" onclick="scanWiFi()">📡 Connect to Internet</button>
    <div id="wifiSetup">
      <p>Select WiFi Network:</p>
      <select id="networkList"><option>Scanning...</option></select>
      <input type="password" id="wifiPass" placeholder="WiFi Password">
      <button class="action-btn" style="background:#f39c12;" onclick="connectWiFi()">Connect</button>
    </div>
  </div>

  <script>
    let r1State = false;
    let r2State = false;

    function toggleRelay(num) {
      let state = num === 1 ? !r1State : !r2State;
      let action = state ? 'on' : 'off';
      fetch(`/relay${num}/${action}`).then(response => {
        if(response.ok) {
          if(num === 1) { r1State = state; document.getElementById('sw1').className = state ? 'switch-btn active' : 'switch-btn'; }
          if(num === 2) { r2State = state; document.getElementById('sw2').className = state ? 'switch-btn active' : 'switch-btn'; }
        }
      });
    }

    function startVoice() {
      const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
      if (!SpeechRecognition) { alert("Voice control not supported."); return; }
      const recognition = new SpeechRecognition();
      recognition.lang = 'en-US';
      document.getElementById('voiceLog').innerText = "Listening...";
      recognition.onresult = (event) => {
        let command = event.results[0][0].transcript.toLowerCase();
        document.getElementById('voiceLog').innerText = "Heard: " + command;
        if(command.includes("light")) toggleRelay(1);
        if(command.includes("fan")) toggleRelay(2);
      };
      recognition.start();
    }

    function scanWiFi() {
      document.getElementById('wifiSetup').style.display = 'block';
      fetch('/scan').then(res => res.text()).then(data => {
        let networks = data.split(',');
        let options = '';
        networks.forEach(net => { if(net) options += `<option value="${net}">${net}</option>`; });
        document.getElementById('networkList').innerHTML = options;
      });
    }

    function connectWiFi() {
      let ssid = document.getElementById('networkList').value;
      let pass = document.getElementById('wifiPass').value;
      alert("Attempting to connect...");
      fetch(`/connect?ssid=${encodeURIComponent(ssid)}&pass=${encodeURIComponent(pass)}`);
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Active Low রিলে শুরুতে অফ রাখার জন্য HIGH দিতে হয়
  digitalWrite(RELAY1_PIN, HIGH); 
  digitalWrite(RELAY2_PIN, HIGH);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
  
  Serial.println("\nESP32 AP Started.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", index_html);
  });

  // রিলে অন করতে LOW এবং অফ করতে HIGH (Active Low logic)
  server.on("/relay1/on", []() { digitalWrite(RELAY1_PIN, LOW); server.send(200, "text/plain", "OK"); });
  server.on("/relay1/off", []() { digitalWrite(RELAY1_PIN, HIGH); server.send(200, "text/plain", "OK"); });
  server.on("/relay2/on", []() { digitalWrite(RELAY2_PIN, LOW); server.send(200, "text/plain", "OK"); });
  server.on("/relay2/off", []() { digitalWrite(RELAY2_PIN, HIGH); server.send(200, "text/plain", "OK"); });

  server.on("/scan", []() {
    int n = WiFi.scanNetworks();
    String networkList = "";
    for (int i = 0; i < n; ++i) {
      networkList += WiFi.SSID(i);
      if(i < n - 1) networkList += ",";
    }
    server.send(200, "text/plain", networkList);
  });

  server.on("/connect", []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    WiFi.begin(ssid.c_str(), pass.c_str());
    server.send(200, "text/plain", "Connecting...");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  
  if (WiFi.status() == WL_CONNECTED) {
    static bool connected = false;
    if (!connected) {
      Serial.println("\nWiFi Connected!");
      Serial.print("Local IP: ");
      Serial.println(WiFi.localIP());
      connected = true;
    }
  }
}