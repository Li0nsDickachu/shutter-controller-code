#pragma once

void put_matrix(uint16_t matrix[5]);

void hardware_init();

void delay_ms(double ms);

enum events {
    EVENT_LEFT_BUTTON = 1 << 0,
    EVENT_RIGHT_BUTTON = 1 << 1,
    EVENT_BOTH_BUTTONS = 1 << 2
};

enum events get_and_clear_button_events();

