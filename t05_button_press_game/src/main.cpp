#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 25

unsigned long startTime;
bool gameStarted = false;

void setup() {
  
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);

  Serial.println("=== ESP32 Reaction Game ===");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Press the button to start!");
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW && !gameStarted) {
    gameStarted = true;
    Serial.println("Get ready...");
    delay(random(1000, 3000)); // Random delay between 2 to 5 seconds
    digitalWrite(LED_PIN, HIGH);
    Serial.println("GO!");
    startTime = millis();
  }
  if(gameStarted && digitalRead(BUTTON_PIN) == LOW) {
    unsigned long reactionTime = millis() - startTime;
    Serial.print("Reaction Time: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    gameStarted = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("Press the button to start again!");
  }
}
