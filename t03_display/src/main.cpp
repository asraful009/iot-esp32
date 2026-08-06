#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

int num1 = 0;
int num2 = 0;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 6 * 3600;  // Bangladesh (UTC+6)
const int daylightOffset_sec = 0;
unsigned long lastRequest = 0;
const unsigned long interval = 5000; // 5 seconds
const char* days[] = {
    "Sun", "Mon", "Tue", "Wed",
    "Thu", "Fri", "Sat"
};

const char* months[] = {
    "Jan", "Feb", "Mar", "Apr",
    "May", "Jun", "Jul", "Aug",
    "Sep", "Oct", "Nov", "Dec"
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Hi All!");


  randomSeed(analogRead(0));
  delay(400);
  lcd.setCursor(0, 1);
  lcd.print("Connecting WiFi...");
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Online!");
  
  Serial.println();
  Serial.println("Connected!");
  // Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

}

void loop() {
  struct tm timeinfo;
    lcd.clear();
  if (getLocalTime(&timeinfo)) {

    char buffer[13];  // 12 characters + null terminator

    strftime(buffer, sizeof(buffer), "%H%M", &timeinfo);
    lcd.setCursor(0, 0);
    lcd.print(buffer);  
  } else {
    lcd.setCursor(0, 0);
    lcd.print("ERROR ON TIME");  
  }
  if (WiFi.status() == WL_CONNECTED) {

    if (millis() - lastRequest >= interval) {
      
      String url = "http://192.168.0.108:8080/";
      url += "?device=ESP32";
      url += "&temp=28";
      url += "&humidity=65";

      HTTPClient http;
      http.begin(url);

      int code = http.GET();

      if (code > 0) {
        String response = http.getString();
        Serial.println(response);
        lcd.setCursor(0, 1);
        lcd.print(response);
        lastRequest = millis();
      } else {
        Serial.printf("HTTP Error: %d\n", code);
        lcd.setCursor(0, 1);
        lcd.print("HTTP Error");
      }

      http.end();
    }
  }

  delay(1000);
}
