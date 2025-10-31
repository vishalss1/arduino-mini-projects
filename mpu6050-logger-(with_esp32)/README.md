# MPU6050 Motion Data Logger (ESP32)

A simple ESP32 project that logs acceleration and gyroscope data from the MPU6050 sensor and stores it on an SD card in CSV format. Ideal for motion tracking and sensor data analysis.

---

### Components
- ESP32 Dev Board  
- MPU6050 (GY-521 module)  
- SD Card Module (SPI interface)

---

### Features
- Reads accelerometer (ax, ay, az) and gyroscope (gx, gy, gz) data  
- Logs readings every 100 ms to [`data.csv`](data.csv)  
- Compact and fast logging with ESP32’s SPI interface  

---

### Folder Contents
- [`code.ino`](code.ino) — ESP32 Arduino code  
- [`data.csv`](data.csv) — Sample output file  
- [`README.md`](README.md) — Project documentation  

---

### Notes
- Connect MPU6050 via I²C (SDA → GPIO 21, SCL → GPIO 22)  
- Connect SD Card via SPI (MOSI → GPIO 23, MISO → GPIO 19, SCK → GPIO 18, CS → GPIO 5)  
- Power all modules using 3.3 V from ESP32  
