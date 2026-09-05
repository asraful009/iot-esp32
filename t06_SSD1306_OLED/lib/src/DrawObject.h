
#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum DrawType {
    DRAW_NONE      = 0b00000000,
    DRAW_DOT       = 0b00000001,
    DRAW_LINE      = 0b00000010,
    DRAW_RECTANGLE = 0b00000100,
    DRAW_CIRCLE    = 0b00001000,
    DRAW_TEXT      = 0b00010000
};

struct DrawObject
{
    DrawType type;

    int x;
    int y;

    int width;
    int height;

    int radius;

    int size = 1;
    char text[256];

    void draw(Adafruit_SSD1306 &oled);

};
