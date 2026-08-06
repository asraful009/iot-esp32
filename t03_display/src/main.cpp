#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int num1 = 0;
int num2 = 0;

void setup() {
  Wire.begin(23, 22);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  lcd.setCursor(0, 1);
  lcd.print("Asraful Islam");

  randomSeed(analogRead(0));

}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("%5d + %5d", num1, num2);
  lcd.setCursor(0, 1);
  lcd.printf("= %5d", num1 + num2);
  num1 = random(1, 101);
  num2 = random(1, 101);
  delay(800);
}
