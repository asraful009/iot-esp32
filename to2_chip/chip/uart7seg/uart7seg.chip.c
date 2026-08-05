
#include "wokwi-api.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


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

typedef struct {
    uart_dev_t uart;
    pin_t pinRST;
    pin_t segA;
    pin_t segB;
    pin_t segC;
    pin_t segD;
    pin_t segE;
    pin_t segF;
    pin_t segG;
    pin_t segDP;
} uart7seg_chip_t;

static void on_uart_rx_data(void *user_data, uint8_t byte) {
    uart7seg_chip_t *chip = (uart7seg_chip_t *) user_data;
    
    uint8_t segments = digits[byte & 0x0F];

    printf("[UART7SEG] Received byte: 0x%02X (%d) => 0x%02X\n", byte, byte, segments);
    
    
    pin_write(chip->segA,  (segments >> 0) & 1);
    pin_write(chip->segB,  (segments >> 1) & 1);
    pin_write(chip->segC,  (segments >> 2) & 1);
    pin_write(chip->segD,  (segments >> 3) & 1);
    pin_write(chip->segE,  (segments >> 4) & 1);
    pin_write(chip->segF,  (segments >> 5) & 1);
    pin_write(chip->segG,  (segments >> 6) & 1);
    pin_write(chip->segDP, (segments >> 7) & 1);
}

void chip_init() {
    uart7seg_chip_t *chip = malloc(sizeof(uart7seg_chip_t));

    chip->pinRST   = pin_init("RST", INPUT_PULLUP);
    chip->segA    = pin_init("a", OUTPUT);
    chip->segB    = pin_init("b", OUTPUT);
    chip->segC    = pin_init("c", OUTPUT);
    chip->segD    = pin_init("d", OUTPUT);
    chip->segE    = pin_init("e", OUTPUT);
    chip->segF    = pin_init("f", OUTPUT);
    chip->segG    = pin_init("g", OUTPUT);
    chip->segDP   = pin_init("dp", OUTPUT);

    const uart_config_t uart_config = {
        .rx = pin_init("RX", INPUT),
        .tx = 0, // Not used in this example
        .baud_rate = 9600,
        .rx_data = on_uart_rx_data,
        .user_data = chip,
    };

    chip->uart = uart_init(&uart_config);
    printf("UART7SEG Chip Initialized and Listening on RX Pin\n");
}
