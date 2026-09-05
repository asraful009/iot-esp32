#include <Arduino.h>
#include <Display.h> 
#include <Config1306.h>

Display display;

void setup() {
    display.begin();
}

void loop() {
    for (int i = 0; i < MAX_DRAW_OBJECTS; i++) {
        DrawObject dot;
        dot.type = DRAW_DOT;
        dot.x = random(0, SCREEN_WIDTH);
        dot.y = random(0, SCREEN_HEIGHT);
        display.addDrawObject(dot);
    }
    display.draw();
    delay(400);
}
