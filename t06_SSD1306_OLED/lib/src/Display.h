
#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DrawObject.h"
#include "Config1306.h"

class Display {
public:
    Display();
    void begin();
    
    void clear();
    void addDrawObject(const DrawObject &drawObject);
    void draw();

private:
    Adafruit_SSD1306 oled;
    DrawObject drawObjects[MAX_DRAW_OBJECTS];
    int drawObjectCount = 0;

};

