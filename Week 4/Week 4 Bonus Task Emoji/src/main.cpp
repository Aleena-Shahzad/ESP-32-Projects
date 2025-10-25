/* EMOJI

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
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  int cx = SCREEN_WIDTH / 2;
  int cy = SCREEN_HEIGHT / 2;
  int r = 28;

  // Outer circle
  display.drawCircle(cx, cy, r, WHITE);

  // Star center to top
  display.drawLine(cx, cy, cx, cy - r, WHITE);

  // Star center to bottom-left
  float angle1 = 210 * 3.14159 / 180;  // 210 degrees
  int x1 = cx + (int)(r * cos(angle1));
  int y1 = cy + (int)(r * sin(angle1));
  display.drawLine(cx, cy, x1, y1, WHITE);

  // Star center to bottom-right
  float angle2 = 330 * 3.14159 / 180;  // 330 degrees
  int x2 = cx + (int)(r * cos(angle2));
  int y2 = cy + (int)(r * sin(angle2));
  display.drawLine(cx, cy, x2, y2, WHITE);

  // Optional inner lines for thickness (looks better on small screen)
  display.drawLine(cx+1, cy, cx+1, cy - r, WHITE);
  display.drawLine(cx-1, cy, cx-1, cy - r, WHITE);

  display.display();
}

void loop() {}

