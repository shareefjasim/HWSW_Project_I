#include <Arduino.h>

// Pin assignments (adjust as needed for your board/pin usage)
#define PIR_PIN       D9   // Digital input from PIR sensor
#define BUTTON1_PIN   D4   // Button 1 input
#define BUTTON2_PIN   D5   // Button 2 input
#define LED_PIN       D10  // LED output (possibly onboard LED on some XIAO boards)

void setup() {
  Serial.begin(115200);

  // Configure PIR sensor pin
  pinMode(PIR_PIN, INPUT);

  // Configure buttons with internal pull-ups
  // -> Pressing the button will read LOW
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  // Configure LED pin as output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off

  Serial.println("=== PIR + 2 Buttons + LED Test (XIAO ESP32C3) ===");
  Serial.println("Waiting a bit for the PIR sensor to stabilize...");
  delay(2000); // Some PIR sensors need time to warm up
  Serial.println("Ready!");
}

void loop() {
  // 1. Read PIR sensor (digital: 0 or 1)
  int pirValue = digitalRead(PIR_PIN);

  // Print PIR reading
  Serial.print("PIR reading: ");
  Serial.println(pirValue);

  // If motion is detected, print a message
  if (pirValue == HIGH) {
    Serial.println("Motion detected!");
  }

  // 2. Read the two buttons
  // Because we used INPUT_PULLUP, a pressed button reads LOW
  bool button1Pressed = (digitalRead(BUTTON1_PIN) == LOW);
  bool button2Pressed = (digitalRead(BUTTON2_PIN) == LOW);

  // Print button states
  Serial.print("Button1: ");
  Serial.print(button1Pressed ? "PRESSED" : "NOT pressed");
  Serial.print(" | Button2: ");
  Serial.println(button2Pressed ? "PRESSED" : "NOT pressed");

  // 3. Control the LED
  // Turn LED on if EITHER button is pressed
  if (button1Pressed) {
    digitalWrite(LED_PIN, HIGH);
  } 
  if (button2Pressed){
    digitalWrite(LED_PIN, LOW);
  }

  // Delay to avoid spamming the serial monitor
  delay(500);
}
