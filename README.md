# ESP32 WiFi Monitor 📡

WiFi monitor for ESP32 DevKit V1 with 1.8" TFT display (ST7735 & ST7735S, 128x160).

Displays: **SSID, password, IP address, MAC address, signal strength**.

---

## 🎮 Controls

| Action | Result |
|--------|--------|
| **Short press BOOT** | Scroll through menu items |
| **Hold BOOT** (0.6 sec) | Select item / return to menu |

---

## 📦 Components

- ESP32 DevKit V1 (TYPE-C or MICRO USB)
- 1.8" SPI TFT display (ST7735S & ST7735, 128x160)
- Female-to-female jumper wires (8 pieces, Dupont)

---

## 🔌 Wiring

| TFT Display | ESP32 DevKit V1 |
|-------------|-----------------|
| VCC         | 3.3V            |
| GND         | GND             |
| LED         | 3.3V (or GPIO21 for PWM control) |
| SCL (SCK)   | GPIO 18         |
| SDA (MOSI)  | GPIO 23         |
| RES (RST)   | GPIO 4          |
| DC (AO)     | GPIO 2          |
| CS          | GPIO 5          |

> Connect LED directly to 3.3V for always-on backlight.

---

## 📁 Installation

1. Install Arduino IDE
2. Install **TFT_eSPI** library by Bodmer
3. Configure `User_Setup.h` (in User_setup.h)
4. Upload `WiFi_Monitor.ino` to your ESP32

---

## 📱 Displayed Info

| Menu Item | What it shows |
|-----------|----------------|
| SSID      | Your WiFi network name |
| PASSWORD  | Your WiFi password |
| IP ADDRESS| ESP32's IP address on the network |
| MAC ADDRESS| ESP32's MAC address |
| SIGNAL    | Signal strength (dBm and percentage) |

---

## ⚠️ Important

- Replace `YOUR_SSID` and `YOUR_PASSWORD` with your actual WiFi credentials before uploading
- Display is 3.3V logic only — DO NOT CONNECT TO 5V!!!

- Good use ☺️
