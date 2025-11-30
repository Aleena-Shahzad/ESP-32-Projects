#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==== Pin Definitions ====
#define BUTTON_MODE 25
#define BUTTON_RESET 26
#define LED_RED 18
#define LED_GREEN 19
#define LED_BLUE 23

// ==== OLED Setup ====
Adafruit_SSD1306 oledDisplay(128, 64, &Wire, -1);

// ==== Global Variables ====
int currentMode = 0;
unsigned long previousMillis = 0;
bool blinkState = false;
int brightnessLevel = 0;
int fadeDirection = 5;  // +5 = fade in, -5 = fade out

// ==== Function Prototypes ====
void displayCurrentMode();
void setAllLEDs(int brightness);

void setup() {
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // Initialize I2C & OLED
  Wire.begin(21, 22);
  oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  displayCurrentMode();
}

void loop() {
  // Button to change mode
  if (digitalRead(BUTTON_MODE) == LOW) {
    delay(200);  // Debounce
    currentMode = (currentMode + 1) % 4;
    displayCurrentMode();
  }

  // Button to reset mode
  if (digitalRead(BUTTON_RESET) == LOW) {
    delay(200);
    currentMode = 0;
    setAllLEDs(0);
    displayCurrentMode();
  }

  // ---- Mode Behaviors ----
  if (currentMode == 0) {
    // Mode 1: All OFF
    setAllLEDs(0);
  } 
  else if (currentMode == 1) {
    // Mode 2: Alternate Blink
    if (millis() - previousMillis > 500) {
      previousMillis = millis();
      blinkState = !blinkState;

      if (blinkState) {
        analogWrite(LED_RED, 255);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 255);
      } else {
        analogWrite(LED_RED, 0);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE, 0);
      }
    }
  } 
  else if (currentMode == 2) {
    // Mode 3: All ON
    setAllLEDs(255);
  } 
  else if (currentMode == 3) {
    // Mode 4: Smooth Fade
    if (millis() - previousMillis > 20) {
      previousMillis = millis();
      brightnessLevel += fadeDirection;
      if (brightnessLevel >= 255 || brightnessLevel <= 0) fadeDirection = -fadeDirection;
      setAllLEDs(brightnessLevel);
    }
  }
}

// ==== Helper Functions ====
void setAllLEDs(int brightness) {
  analogWrite(LED_RED, brightness);
  analogWrite(LED_GREEN, brightness);
  analogWrite(LED_BLUE, brightness);
}

void displayCurrentMode() {
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(2);
  oledDisplay.setTextColor(WHITE);
  oledDisplay.setCursor(0, 10);
  oledDisplay.print("MODE ");
  oledDisplay.println(currentMode + 1);

  oledDisplay.setTextSize(1);
  oledDisplay.setCursor(0, 40);

  if (currentMode == 0) oledDisplay.print("OFF");
  if (currentMode == 1) oledDisplay.print("BLINK");
  if (currentMode == 2) oledDisplay.print("ON");
  if (currentMode == 3) oledDisplay.print("FADE");

  oledDisplay.display();
}
