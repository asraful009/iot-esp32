#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

#define FAN_PIN    25
#define LIGHT_PIN  26
#define PUMP_PIN   27


const char* ssid = "black";
const char* password = "1";
const char* API_URL = "http://192.168.0.104:8080/api/device/id=114der";

unsigned long lastRequest = 0;
const unsigned long requestInterval = 2000; // 2 seconds

struct Device {
  int id;
  String name;
  bool online;
};


struct Sensor {
  float temperature;
  float humidity;
};

struct Cmd {
  bool fan;
  bool light;
  bool pump;
};

struct ApiData {
  Device device;
  Cmd cmd;
  Sensor sensor;
};

ApiData deviceData;
BluetoothSerial SerialBT;

void parseApiResponse(const String& response) {

  JsonDocument doc;

  if (deserializeJson(doc, response)) {
    Serial.println("JSON error");
    return;
  }

  deviceData.device.id     = doc["device"]["id"] | 0;
  deviceData.device.name   = doc["device"]["name"] | "";
  deviceData.device.online = doc["device"]["online"] | false;

  deviceData.sensor.temperature = doc["sensor"]["temperature"] | 0.0;
  deviceData.sensor.humidity    = doc["sensor"]["humidity"] | 0.0;

  deviceData.cmd.fan   = doc["cmd"]["fan"] | false;
  deviceData.cmd.light = doc["cmd"]["light"] | false;
  deviceData.cmd.pump  = doc["cmd"]["pump"] | false;
}

void updateRelays() {

  digitalWrite(FAN_PIN,   deviceData.cmd.fan);
  digitalWrite(LIGHT_PIN, deviceData.cmd.light);
  digitalWrite(PUMP_PIN,  deviceData.cmd.pump);
}

void setup() {
  
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Connecting to WiFi...");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
    if (i++ > 3) {
      Serial.print("\r");
    }
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  pinMode(FAN_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);



  if (!SerialBT.begin("ESP32_114der")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
}

void loop() {

   if (millis() - lastRequest >= requestInterval) {
    lastRequest = millis();
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(API_URL);
      int httpCode = http.GET();
      if (httpCode > 0) {
        String response = http.getString();
        Serial.println(response);
        parseApiResponse(response);
        updateRelays();
      }
      http.end();
    }
    if (SerialBT.available()) {
      // String command = SerialBT.readStringUntil('\n');
      // Serial.println(command);
      SerialBT.println("ESP32 FAN: " + String(deviceData.cmd.fan ? "ON" : "OFF"));
      SerialBT.println("ESP32 LIGHT: " + String(deviceData.cmd.light ? "ON" : "OFF"));
      SerialBT.println("ESP32 PUMP: " + String(deviceData.cmd.pump ? "ON" : "OFF"));
    }
  }

}
