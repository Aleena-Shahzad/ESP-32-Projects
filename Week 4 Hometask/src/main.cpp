#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Create display object (I2C address 0x3C for most OLEDs)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Start serial monitor (optional)
  Serial.begin(115200);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  
  // Set text properties
  display.setTextSize(1);              // 1 = small text
  display.setTextColor(SSD1306_WHITE); // White color text
  display.setCursor(20, 25);           // X=20, Y=25 for center-ish placement

  // Print Name & ID
  display.print("Name: Aleena");
  display.setCursor(20, 40);  // Move cursor below
  display.print("ID: 12345");

  // Draw rectangle around text
  display.drawRect(15, 20, 100, 30, SSD1306_WHITE);
  // (X, Y, Width, Height, Color)

  // Show everything on the display
  display.display();
}

void loop() {
  
}