#include <Arduino.h>
#include <stdio.h>

#define PIN0 16
#define PIN1 17
#define PIN2 18
#define PIN3 19

int i=0;

void setup() {
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  i=0;
}

void loop() {
  printf("i=%d\n", i);

  digitalWrite(PIN0, (i >> 0) & 1);
  digitalWrite(PIN1, (i >> 1) & 1);
  digitalWrite(PIN2, (i >> 2) & 1);
  digitalWrite(PIN3, (i >> 3) & 1);
  delay(300);
  i++;
  i = i % 16;

}
