#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "MPU6050.h"

MPU6050 mpu;

const int chipSelect = 10;  // SD card CS pin
File dataFile;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Initialize SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized.");

  // Create/open file
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("ax,ay,az,gx,gy,gz"); // CSV header
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
  }

  delay(1000);
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read raw data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Print to serial (for debugging)
  Serial.print("aX = "); Serial.print(ax);
  Serial.print(" | aY = "); Serial.print(ay);
  Serial.print(" | aZ = "); Serial.print(az);
  Serial.print(" | gX = "); Serial.print(gx);
  Serial.print(" | gY = "); Serial.print(gy);
  Serial.print(" | gZ = "); Serial.println(gz);

  // Save to SD card
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(ax); dataFile.print(",");
    dataFile.print(ay); dataFile.print(",");
    dataFile.print(az); dataFile.print(",");
    dataFile.print(gx); dataFile.print(",");
    dataFile.print(gy); dataFile.print(",");
    dataFile.println(gz);
    dataFile.close();
  } else {
    Serial.println("Error opening file for writing!");
  }

  delay(100); // 10 samples per second
}
