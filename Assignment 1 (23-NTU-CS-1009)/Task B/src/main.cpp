#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
Adafruit_SSD1306 oledDisplay(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ==== Pin Definitions ====
#define LED_RED 18
#define LED_GREEN 19
#define LED_BLUE 23
#define BUZZER_PIN 27
#define BUTTON_INPUT 25  // Single button

#define LONG_PRESS_THRESHOLD 1500  // 1.5 seconds

// ==== Global Variables ====
bool ledsOn = false;
bool buttonHeld = false;
unsigned long pressStartTime = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_INPUT, INPUT_PULLUP);  // Button to GND

  // OLED Initialization
  if (!oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED initialization failed!"));
    for (;;);
  }

  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(1);
  oledDisplay.setTextColor(SSD1306_WHITE);
  oledDisplay.setCursor(0, 0);
  oledDisplay.println("System Ready");
  oledDisplay.display();

  // Start all devices off
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  bool isButtonPressed = (digitalRead(BUTTON_INPUT) == LOW);

  // When button first pressed
  if (isButtonPressed && !buttonHeld) {
    buttonHeld = true;
    pressStartTime = millis();
  }

  // When button released
  if (!isButtonPressed && buttonHeld) {
    unsigned long pressDuration = millis() - pressStartTime;
    buttonHeld = false;

    if (pressDuration >= LONG_PRESS_THRESHOLD) {
      handleLongPress();
    } else {
      handleShortPress();
    }
  }
}

// ==== Short Press → Toggle LEDs ====
void handleShortPress() {
  ledsOn = !ledsOn;

  digitalWrite(LED_RED, ledsOn);
  digitalWrite(LED_GREEN, ledsOn);
  digitalWrite(LED_BLUE, ledsOn);

  oledDisplay.clearDisplay();
  oledDisplay.setCursor(0, 0);
  oledDisplay.println("Short Press Detected");
  oledDisplay.println(ledsOn ? "LEDs: ON" : "LEDs: OFF");
  oledDisplay.display();

  Serial.println("Short Press Detected");
}

// ==== Long Press → Play Buzzer ====
void handleLongPress() {
  oledDisplay.clearDisplay();
  oledDisplay.setCursor(0, 0);
  oledDisplay.println("Long Press Detected");
  oledDisplay.println("Playing buzzer tone...");
  oledDisplay.display();

  Serial.println("Long Press Detected - Playing tone");

  tone(BUZZER_PIN, 1000);  // 1 kHz tone
  delay(500);              // Play for 0.5 s
  noTone(BUZZER_PIN);
}
