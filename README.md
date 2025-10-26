# 🔥 ESP32 Flame Detection Captive Portal

## 📘 Description
This project uses an **ESP32 microcontroller** and a **flame sensor** to create a **Wi-Fi Captive Portal** that displays real-time fire detection status.

When powered on, the ESP32 starts its own Wi-Fi network (Access Point).  
Users can connect to it using a smartphone or laptop, and they’ll automatically be redirected to a web page showing:

- 🔥 Whether a **flame is detected** or not  
- 🔢 The **number of times** a flame has been detected  

The portal automatically refreshes every 2 seconds, allowing live updates without needing internet access.

---

## ⚙️ Features
- 🧠 **Wi-Fi Captive Portal:** Automatically opens the flame detection dashboard on connection  
- 🔥 **Real-Time Flame Detection:** Displays live sensor readings from the flame sensor  
- 📈 **Detection Counter:** Shows total number of flame detection events  
- 📡 **Offline Operation:** Works completely without an internet connection  
- 🧩 **Simple Hardware Setup:** Uses only an ESP32 and a flame sensor module  

---

## 🛠️ Hardware Components
| Component | Quantity | Description |
|------------|-----------|-------------|
| ESP32 Dev Board | 1 | Main microcontroller |
| Flame Sensor Module | 1 | Detects presence of flame |
| Jumper Wires | As needed | For connections |
| Breadboard (optional) | 1 | For prototyping |

---

## 🔌 Circuit Connections
| Flame Sensor Pin | ESP32 Pin | Description |
|------------------|------------|-------------|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| DO (Digital Output) | GPIO 35 | Flame detection signal |

> ⚠️ If your flame sensor requires 5V input, use a **voltage divider (1kΩ + 2kΩ)** on the DO line to safely drop signal to 3.3V for the ESP32.

---

## 🧾 How It Works
1. ESP32 boots and starts an **Access Point** named `FlameDetector`.
2. The onboard web server and DNS server simulate a **captive portal**.  
3. When a user connects to the Wi-Fi, they’re redirected to a web page showing the flame status.  
4. The flame sensor continuously monitors for flame presence:  
   - ✅ “No Flame” (normal state)  
   - 🔥 “Flame Detected!” (trigger event and count increment)  

---

## 🚀 How to Use
1. Upload the code to your ESP32 using Arduino IDE.  
2. Open Serial Monitor to confirm Wi-Fi setup.  
3. Connect your phone or laptop to the **“FlameDetector”** Wi-Fi.  
4. When connected, you’ll be redirected automatically — or open `http://192.168.4.1/`.  
5. View live flame detection status on the page.  

---

## 🧰 Optional Add-Ons
- Add a **buzzer** or **LED** to alert when a flame is detected.  
- Store detection logs in EEPROM or send data via MQTT for IoT integration.  
- Add AJAX or WebSocket for instant updates (no page refresh).  

---

## 🧑‍💻 Tech Stack
- **Microcontroller:** ESP32  
- **Language:** C++ (Arduino Framework)  
- **Libraries:**  
  - `WiFi.h` – for Access Point setup  
  - `WebServer.h` – for HTTP server  
  - `DNSServer.h` – for captive portal redirection  

---

## 📸 Preview
When connected to the ESP32’s Wi-Fi, you’ll see:

---

## 🏁 Future Improvements
- Integration with **Firebase or Blynk** for cloud-based alerts  
- Mobile notification or SMS alert when fire is detected  
- Use **DHT11 sensor** alongside for temperature-based alerts  

---

## 🧑‍🔧 Author
**T Rohan Kini**  
B.Tech Computer Science and Engineering  
NMAM Institute of Technology  

---

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/rohankini) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/RohanKinirk) 
