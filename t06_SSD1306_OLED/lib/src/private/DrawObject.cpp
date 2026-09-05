
#include <Arduino.h>
#include "DrawObject.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void DrawObject::draw(Adafruit_SSD1306 &oled)
{
    switch (type)
    {
        case DRAW_DOT:
            oled.drawPixel(
                x,
                y,
                SSD1306_WHITE
            );
            break;

        case DRAW_LINE:
            oled.drawLine(
                x,
                y,
                x + width,
                y + height,
                SSD1306_WHITE
            );
            break;

        case DRAW_RECTANGLE:
            oled.drawRect(
                x,
                y,
                width,
                height,
                SSD1306_WHITE
            );
            break;

        case DRAW_CIRCLE:
            oled.drawCircle(
                x,
                y,
                radius,
                SSD1306_WHITE
            );
            break;

        case DRAW_TEXT:
            oled.setCursor(x, y);
            oled.print(text);
            break;

        case DRAW_NONE:
        default:
            break;
    }
}