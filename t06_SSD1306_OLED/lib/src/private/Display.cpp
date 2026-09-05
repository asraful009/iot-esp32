
#include <Arduino.h>
#include "Display.h"

#include "Config1306.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <stdexcept>

Display::Display() :
oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{}

void Display::begin()
{
    Wire.begin(SCREEN_I2C_SDA, SCREEN_I2C_SCL);
    if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS)) 
    {
        Serial.println(F("SSD1306 allocation failed, check your wiring or I2C address!"));
        throw std::runtime_error("SSD1306 initialization failed");
    }
    oled.clearDisplay();
    
}

void Display::clear()
{
    oled.clearDisplay();
}

void Display::addDrawObject(const DrawObject &drawObject)
{
    // Implementation for adding a draw object
    if (drawObjectCount >= MAX_DRAW_OBJECTS) 
    {
        Serial.println(F("Maximum number of draw objects reached!"));
        return;
    }

    drawObjects[drawObjectCount++] = drawObject;

}

void Display::draw()
{
    // Implementation for drawing all draw objects
    oled.clearDisplay();
    for (int i = 0; i < drawObjectCount; i++) 
    {
        drawObjects[i].draw(oled);
    }
    oled.display(); 
}
