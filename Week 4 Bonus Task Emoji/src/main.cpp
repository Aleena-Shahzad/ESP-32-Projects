/*  EMOJI

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.drawCircle(64, 32, 30, WHITE);       // face outline
  display.fillCircle(54, 24, 4, WHITE);        // left eye
  display.fillCircle(74, 24, 4, WHITE);        // right eye

  // smile (drawn using a line + pixels)
  for (int x = 48; x <= 80; x++) {
    int y = 44 + (int)(0.02 * (x - 64) * (x - 64) / 2); 
    display.drawPixel(x, y, WHITE);
  }

  display.display();
}

void loop() 
{}
*/

/* AVATAR

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Head
  display.fillCircle(64, 32, 26, WHITE);
  display.fillCircle(64, 32, 24, BLACK);

  // Hair
  for (int x = 38; x <= 90; x++) {
    int y = 16 - (int)(0.05 * (x - 64) * (x - 64));
    display.drawPixel(x, y, WHITE);
  }

  // Eyes
  display.fillCircle(54, 30, 4, WHITE);
  display.fillCircle(74, 30, 4, WHITE);
  display.fillCircle(54, 30, 2, BLACK);
  display.fillCircle(74, 30, 2, BLACK);

  // Mouth (smile)
  for (int x = 50; x <= 78; x++) {
    int y = 45 + (int)(0.02 * (x - 64) * (x - 64) / 2);
    display.drawPixel(x, y, WHITE);
  }

  // Ears
  display.fillCircle(38, 32, 4, WHITE);
  display.fillCircle(90, 32, 4, WHITE);

  // Neck
  display.fillRect(58, 52, 12, 8, WHITE);

  // Body (shirt)
  display.fillRect(46, 60, 36, 8, WHITE);

  display.display();
}

void loop() {}
*/



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Simple Nike Swoosh (approximate)
const unsigned char nike_logo[] PROGMEM = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000011, 0b00000000,
  0b00000000, 0b00000000, 0b00000111, 0b10000000,
  0b00000000, 0b00000000, 0b00001111, 0b11000000,
  0b00000000, 0b00000000, 0b00011111, 0b11100000,
  0b00000000, 0b00000000, 0b00111111, 0b11110000,
  0b00000000, 0b00000000, 0b01111111, 0b11111000,
  0b00000000, 0b00000000, 0b00011111, 0b11100000,
  0b00000000, 0b00000000, 0b00001111, 0b11000000,
  0b00000000, 0b00000000, 0b00000111, 0b10000000,
  0b00000000, 0b00000000, 0b00000011, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000
};

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();

  // Draw Nike logo
  display.drawBitmap(40, 10, nike_logo, 48, 14, SSD1306_WHITE);

  // Write NIKE text under it
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 35);
  display.print("NIKE");

  display.display();
}

void loop() {
}
