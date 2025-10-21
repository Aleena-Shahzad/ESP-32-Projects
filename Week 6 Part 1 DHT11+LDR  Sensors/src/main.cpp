//Aleena Shahzad
//23-NTU-CS-1009
//BSCS 5 A
//ESP32 Sensor Station: DHT22 and LDR with OLED Display

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin configuration ---
#define DHTPIN 14         // DHT22 data pin
#define DHTTYPE DHT22     // Change to DHT11 if needed
#define LDR_PIN 34        // LDR analog pin
#define SDA_PIN 21        // I2C SDA
#define SCL_PIN 22        // I2C SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT sensor setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup ---
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Sensor Station");

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Initialize DHT sensor
  dht.begin();
  delay(1000);
}

// --- Loop ---
void loop() {
  // Read DHT22 data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read LDR data
  int adcValue = analogRead(LDR_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;

  // Check if DHT22 failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT22 sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("DHT22 Error!");
    display.display();
    delay(2000);
    return;
  }

  // Print to Serial Monitor
  Serial.printf("Temp: %.2f °C | Humidity: %.2f %% | LDR: %d (%.2f V)\n",
                temperature, humidity, adcValue, voltage);

  // Display on OLED
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ESP32 IoT Station");

  display.setCursor(0, 12);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 24);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 36);
  display.print("LDR ADC: ");
  display.println(adcValue);

  display.setCursor(0, 48);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  display.display();

  delay(2000); // update every 2 seconds
}