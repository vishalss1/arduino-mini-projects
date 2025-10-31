# ESP32 Crash Detection and Alert System

A mini project using **ESP32**, **MPU6050**, **OLED display**, **SD card**, and **audio alert** system to detect crashes and log data.  
When a crash is detected, the LED and buzzer activate, and the display blinks “CRASHED!”.  
Otherwise, live MPU6050 sensor data is displayed and recorded to the SD card.

---

### Components
- ESP32 Dev Board  
- MPU6050 (GY-521 module)  
- 1.3" OLED Display (SH1106 I²C)  
- SD Card Module (SPI interface)  
- PAM8403 Amplifier Module + 8Ω Speakers (x2)  
- Red LED + 220Ω resistor  
- 0.1µF capacitors (for noise filtering)  

---

### Features
- Reads real-time accelerometer and gyroscope data  
- Detects crashes based on acceleration threshold  
- Logs data into [`crashlog.csv`](crashlog.csv) on SD card  
- Displays live data when normal  
- On crash:  
  - OLED blinks **“CRASHED!”**  
  - LED turns on and blinks  
  - Speakers buzz via amplifier  
  - Logging stops and alert mode continues  

---

### Folder Contents
- [`code.ino`](code.ino) — ESP32 Arduino code  
- [`crashlog.csv`](crashlog.csv) — Sample SD card log output  
- [`README.md`](README.md) — Project documentation  

---

### Notes
- **Connections:**
  - OLED → `SDA=21`, `SCL=22`, `VCC=3.3V`, `GND=GND`  
  - MPU6050 → `SDA=21`, `SCL=22`, `VCC=3.3V`, `GND=GND`  
  - SD Card → `CS=5`, `MOSI=23`, `MISO=19`, `SCK=18`, `VCC=5V`, `GND=GND`  
  - LED → `GPIO27` (with 220Ω resistor to GND)  
  - Amplifier:
    - `L` → `GPIO25` (via 220Ω resistor)  
    - `R` → `GPIO26` (via 220Ω resistor)  
    - `T` → `GND`  
    - `+` → `5V`  
    - `–` → `GND`  
  - All grounds must be **common**  

- Add 0.1µF capacitor between each DAC output and GND to reduce noise.  
- Power the amplifier from 5V, and ensure the ESP32 and amp share the same GND.  
