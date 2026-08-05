#include <Arduino.h>
#include <stdio.h>

#define PIN0 16
#define PIN1 17
#define PIN2 18
#define PIN3 19
int number = 0;



HardwareSerial uart7Seg(2);

void setup() {
  // Serial.begin(115200);
  uart7Seg.begin(9600, SERIAL_8N1, 13, 12); // RX=13, TX=12

  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  number = 0;
}

void loop() {
  printf("number :: %d\n", number);
  digitalWrite(PIN0, (number >> 0) & 1);
  digitalWrite(PIN1, (number >> 1) & 1);
  digitalWrite(PIN2, (number >> 2) & 1);
  digitalWrite(PIN3, (number >> 3) & 1);
  uart7Seg.write(number);
  number = (number + 1) % 16;
  delay(400);
}
