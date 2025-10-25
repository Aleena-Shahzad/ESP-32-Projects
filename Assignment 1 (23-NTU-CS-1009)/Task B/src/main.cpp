#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// Pin configuration
#define LED1 18
#define LED2 19
#define LED3 23
#define BUZZER 27
#define BTN_MODE 25  // Single button

#define LONG_PRESS_TIME 1500  // 1.5 seconds

// Variables
bool ledState = false;
bool isPressed = false;
unsigned long pressStart = 0;

void setup() {
  Serial.begin(115200);

  // Pin modes
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);  // Button to GND

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("System Ready");
  display.display();

  // Turn everything off initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  bool buttonPressed = (digitalRead(BTN_MODE) == LOW);

  if (buttonPressed && !isPressed) {
    isPressed = true;
    pressStart = millis();
  }

  if (!buttonPressed && isPressed) {
    unsigned long pressDuration = millis() - pressStart;
    isPressed = false;

    if (pressDuration >= LONG_PRESS_TIME) 
    {
      longPressAction();
    } 
    else 
    {
      shortPressAction();
    }
  }
}

// -----------------------
// Short press → Toggle LED
// -----------------------
void shortPressAction() {
  ledState = !ledState;
  digitalWrite(LED1, ledState);
  digitalWrite(LED2, ledState);
  digitalWrite(LED3, ledState);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Short Press Detected");
  display.println(ledState ? "LEDs: ON" : "LEDs: OFF");
  display.display();

  Serial.println("Short Press Detected");
}

// -----------------------
// Long press → Play buzzer
// -----------------------
void longPressAction() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Long Press Detected");
  display.println("Playing buzzer tone...");
  display.display();

  Serial.println("Long Press Detected - Playing tone");

  tone(BUZZER, 1000);   // 1 kHz tone
  delay(500);           // Play for 0.5 s
  noTone(BUZZER);
}