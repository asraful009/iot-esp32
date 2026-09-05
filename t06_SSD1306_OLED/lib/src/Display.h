
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
    Display();
    void begin();
    // void clear();
    // void drawText(int x, int y, const char* text);
    // void drawRect(int x, int y, int width, int height);
    // void drawCircle(int x, int y, int radius);
    // void update();

private:
    Adafruit_SSD1306 oled;

};

#endif // DISPLAY_H
