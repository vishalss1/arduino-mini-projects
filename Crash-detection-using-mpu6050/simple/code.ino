#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <SD.h>

// Pin definitions
#define SD_CS 5
#define LED_PIN 27
#define LEFT_PIN 25   // DAC1
#define RIGHT_PIN 26  // DAC2

// Crash sensitivity
#define CRASH_THRESHOLD 2.5  // G-force threshold for crash

// Objects
Adafruit_MPU6050 mpu;
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);
File dataFile;

bool crashed = false;

void setup() {
  Serial.begin(115200);

  // --- OLED setup ---
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 25);
  display.println("Initializing...");
  display.display();

  // --- LED setup ---
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // --- DAC setup ---
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  dacWrite(LEFT_PIN, 0);
  dacWrite(RIGHT_PIN, 0);

  // --- MPU6050 setup ---
  if (!mpu.begin()) {
    displayError("MPU6050 NOT FOUND!");
    while (1);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // --- SD setup ---
  if (!SD.begin(SD_CS)) {
    displayError("SD Card Failed!");
    while (1);
  }

  dataFile = SD.open("/crashlog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time(ms),AccelX,AccelY,AccelZ,Crash");
    dataFile.close();
  }

  display.clearDisplay();
  display.setCursor(20, 25);
  display.println("Ready...");
  display.display();
  delay(1000);
}

void loop() {
  if (crashed) {
    handleCrash();
    return;
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float ax = a.acceleration.x / 9.81;
  float ay = a.acceleration.y / 9.81;
  float az = a.acceleration.z / 9.81;
  float magnitude = sqrt(ax * ax + ay * ay + az * az);

  // --- Log to SD ---
  dataFile = SD.open("/crashlog.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.print(ax, 2);
    dataFile.print(",");
    dataFile.print(ay, 2);
    dataFile.print(",");
    dataFile.print(az, 2);
    dataFile.print(",");
    if (magnitude > CRASH_THRESHOLD) dataFile.println("CRASH");
    else dataFile.println("OK");
    dataFile.close();
  }

  // --- Display data ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Accel (g):");
  display.setCursor(0, 15);
  display.printf("X: %.2f\n", ax);
  display.printf("Y: %.2f\n", ay);
  display.printf("Z: %.2f\n", az);
  display.display();

  // --- Crash detection ---
  if (magnitude > CRASH_THRESHOLD) {
    crashed = true;
    markCrash();
  }

  delay(200);
}

// --- Crash handling ---
void handleCrash() {
  while (true) {
    // Blink "CRASHED!!"
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 20);
    display.println("CRASHED!");
    display.display();

    // LED on and beep
    digitalWrite(LED_PIN, HIGH);
    beep(800, 400); // 800Hz for 400ms

    // Pause
    display.clearDisplay();
    display.display();
    digitalWrite(LED_PIN, LOW);
    silence();
    delay(400);
  }
}

// --- Single crash log marker ---
void markCrash() {
  dataFile = SD.open("/crashlog.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.println("CRASH DETECTED!!!");
    dataFile.close();
  }
}

// --- Simple DAC tone ---
void beep(int freq, int duration) {
  int samples = (1000000 / freq) / 2;
  unsigned long endTime = millis() + duration;
  while (millis() < endTime) {
    dacWrite(LEFT_PIN, 255);
    dacWrite(RIGHT_PIN, 255);
    delayMicroseconds(samples);
    dacWrite(LEFT_PIN, 0);
    dacWrite(RIGHT_PIN, 0);
    delayMicroseconds(samples);
  }
}

// --- Silence speakers ---
void silence() {
  dacWrite(LEFT_PIN, 0);
  dacWrite(RIGHT_PIN, 0);
}

// --- OLED error message ---
void displayError(const char* msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
  Serial.println(msg);
}
