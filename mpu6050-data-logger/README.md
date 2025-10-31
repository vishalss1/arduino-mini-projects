# MPU6050 Motion Data Logger

A simple Arduino project that records acceleration and gyroscope data from the MPU6050 sensor and saves it to an SD card in CSV format. The logged data can be later analyzed in Excel or MATLAB.

---

### Components
- Arduino UNO  
- MPU6050 (GY-521 module)  
- SD Card Module (SPI interface)

---

### Features
- Reads accelerometer (ax, ay, az) and gyroscope (gx, gy, gz) data  
- Logs sensor readings every 100 ms  
- Stores data in [`DATA.csv`](DATA.csv) on the SD card  
- Easy to visualize and analyze motion data  

---

### Folder Contents
- [`motion-data-logger.ino`](motion-data-logger.in0) — Arduino code  
- [`DATA.csv`](DATA.csv) — Sample output file  
- [`README.md`](REDME.md) — Project documentation  

---

### Notes
- Connect MPU6050 via I²C (SDA → A4, SCL → A5)  
- Connect SD Card Module via SPI (MOSI → 11, MISO → 12, SCK → 13, CS → 10)  
- Power both modules using 5V and GND from Arduino UNO  
