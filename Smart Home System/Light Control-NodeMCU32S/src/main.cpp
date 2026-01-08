#define BLYNK_TEMPLATE_ID "TMPL6_pw2-dHe"
#define BLYNK_TEMPLATE_NAME "Home Control System by DUO Tech"
#define BLYNK_AUTH_TOKEN "lW75RznbPciGc3E5adztAa3QV-sKPl2g"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "aleena";
char pass[] = "aleena25";

// Relay pins
const int relayC = 26; // Bulb 1 (BULB 1 in Blynk)
const int relayD = 27; // Bulb 2 (BULB 2 in Blynk)

// Blynk Virtual Pins
#define BLYNK_VPIN_BULB1 V0 // Virtual Pin V0 for BULB 1
#define BLYNK_VPIN_BULB2 V1 // Virtual Pin V1 for BULB 2

void setup()
{
  Serial.begin(115200);
  delay(100);

  // Initialize relay pins
  pinMode(relayC, OUTPUT);
  pinMode(relayD, OUTPUT);
  digitalWrite(relayC, HIGH); // OFF
  digitalWrite(relayD, HIGH); // OFF

  Serial.println("\n\nStarting Blynk Setup...");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("ESP32 Blynk Relay Control Started!");
  delay(500);
}

void loop()
{
  if (Blynk.connected())
  {
    Blynk.run();
  }
  else
  {
    Serial.println("Blynk not connected. Reconnecting...");
    Blynk.connect();
  }

  // Optional: Local serial control still works
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    if (command == "c1")
    {
      digitalWrite(relayC, LOW); // ON
      Blynk.virtualWrite(BLYNK_VPIN_BULB1, 1);
      Serial.println("✅ Bulb C (V0): ON");
    }
    else if (command == "c0")
    {
      digitalWrite(relayC, HIGH); // OFF
      Blynk.virtualWrite(BLYNK_VPIN_BULB1, 0);
      Serial.println("❌ Bulb C (V0): OFF");
    }
    else if (command == "d1")
    {
      digitalWrite(relayD, LOW); // ON
      Blynk.virtualWrite(BLYNK_VPIN_BULB2, 1);
      Serial.println("✅ Bulb D (V1): ON");
    }
    else if (command == "d0")
    {
      digitalWrite(relayD, HIGH); // OFF
      Blynk.virtualWrite(BLYNK_VPIN_BULB2, 0);
      Serial.println("❌ Bulb D (V1): OFF");
    }
    else
    {
      Serial.println("❌ Invalid command! Use: c1/c0, d1/d0");
    }
  }

  delay(100);
}

// Blynk Virtual Pin Handler for BULB 1 (V0)
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // Get value from Blynk app (0 or 1)

  if (pinValue == 1)
  {
    digitalWrite(relayC, LOW); // ON
    Serial.println("✅ Blynk: Bulb 1 (V0) - ON");
  }
  else
  {
    digitalWrite(relayC, HIGH); // OFF
    Serial.println("❌ Blynk: Bulb 1 (V0) - OFF");
  }
}

// Blynk Virtual Pin Handler for BULB 2 (V1)
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // Get value from Blynk app (0 or 1)

  if (pinValue == 1)
  {
    digitalWrite(relayD, LOW); // ON
    Serial.println("✅ Blynk: Bulb 2 (V1) - ON");
  }
  else
  {
    digitalWrite(relayD, HIGH); // OFF
    Serial.println("❌ Blynk: Bulb 2 (V1) - OFF");
  }
}

// Called when Blynk connects
BLYNK_CONNECTED()
{
  Serial.println("✅ Blynk Connected!");
  // Sync virtual pins with actual relay states on connection
  Blynk.syncVirtual(V0, V1);
}