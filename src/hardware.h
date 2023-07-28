#pragma once
#include <stdbool.h>
#include <stdint.h>

void put_matrix(uint16_t matrix[5]);

void hardware_init();

void delay_ms(double ms);

enum events {
    EVENT_LEFT_BUTTON_UP = 1 << 0,
    EVENT_RIGHT_BUTTON_UP = 1 << 1,
    EVENT_BOTH_BUTTONS_UP = 1 << 2,
    EVENT_LEFT_BUTTON_DOWN = 1 << 3,
    EVENT_RIGHT_BUTTON_DOWN = 1 << 4
};

enum events get_and_clear_button_events();

void shutter_button(bool dir);

#define BUTTON_DOWN 1
#define BUTTON_UP 0

#ifdef IN_SIMULATOR
#define PROGMEM
uint8_t pgm_read_byte(const uint8_t *address);
#else
#include <avr/pgmspace.h>
#endif
