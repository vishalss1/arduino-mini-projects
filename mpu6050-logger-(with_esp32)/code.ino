#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "MPU6050.h"

MPU6050 mpu;
File dataFile;

const int CS_PIN = 5;   // SD card CS pin

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL for ESP32

  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("Initializing SD card...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized.");

  // Create CSV header
  dataFile = SD.open("/data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("ax,ay,az,gx,gy,gz");
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
  }

  delay(1000);
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.printf("aX=%d aY=%d aZ=%d gX=%d gY=%d gZ=%d\n", ax, ay, az, gx, gy, gz);

  dataFile = SD.open("/data.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.printf("%d,%d,%d,%d,%d,%d\n", ax, ay, az, gx, gy, gz);
    dataFile.close();
  } else {
    Serial.println("Error writing to data.csv");
  }

  delay(100);  // log every 100 ms
}
