#include "wokwi-api.h"
#include <stdint.h>
#include <stdio.h>

static pin_t pinA, pinB, pinC, pinD;
static pin_t segA, segB, segC, segD, segE, segF, segG;

const uint8_t digits[16] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111, // 9
    0b1110111, // A
    0b1111100, // b (lowercase)
    0b0111001, // C
    0b1011110, // d (lowercase)
    0b1111001, // E
    0b1110001  // F
};

static void update() {
    uint8_t value = 0;
    value |= pin_read(pinA) << 0;
    value |= pin_read(pinB) << 1;
    value |= pin_read(pinC) << 2;
    value |= pin_read(pinD) << 3;

    uint8_t segments = digits[value & 0x0F];

    printf("Value: %d, Segments: 0x%02X\n", value, segments);

    pin_write(segA, (segments >> 0) & 1);
    pin_write(segB, (segments >> 1) & 1);
    pin_write(segC, (segments >> 2) & 1);
    pin_write(segD, (segments >> 3) & 1);
    pin_write(segE, (segments >> 4) & 1);
    pin_write(segF, (segments >> 5) & 1);
    pin_write(segG, (segments >> 6) & 1);
}

void chip_init() {

    pinA = pin_init("A", INPUT);
    pinB = pin_init("B", INPUT);
    pinC = pin_init("C", INPUT);
    pinD = pin_init("D", INPUT);

    segA = pin_init("a", OUTPUT);
    segB = pin_init("b", OUTPUT);
    segC = pin_init("c", OUTPUT);
    segD = pin_init("d", OUTPUT);
    segE = pin_init("e", OUTPUT);
    segF = pin_init("f", OUTPUT);
    segG = pin_init("g", OUTPUT);

    const pin_watch_config_t watch = {
        .edge = BOTH,
        .pin_change = update,
    };

    pin_watch(pinA, &watch);
    pin_watch(pinB, &watch);
    pin_watch(pinC, &watch);
    pin_watch(pinD, &watch);

    update();
}