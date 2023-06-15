#include <stdio.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "defines.h"

void delay_ms(double ms) {
    _delay_ms(ms);
}

void hardware_init() {
    DDR_POWER |= 1 << PIN_POWER;
    PORT_POWER |= 1 << PIN_POWER;

    DDR_BUTT1 &= ~(1 << PIN_BUTT1);
    PORT_BUTT1 |= 1 << PIN_BUTT1; // Vih was mistaken to be higher than it actually turned out to be, to fix, remove R15, and use internal pullup of atmega
    DDR_BUTT2 &= ~(1 << PIN_BUTT2);

    clock_prescale_set(clock_div_1);

    DDRC = 0b00111111;
    DDRD = 0b11111111;

    // interrupt_freq = F_CPU / 64 / (1 << 8)
    TCNT0 = 0;
    OCR0A = 200; // brightness
    TCCR0A = 0x0;
    TCCR0B |= (1<<CS00) | (1<<CS01); // prescaler 64
    TIMSK0 |= (1<<TOIE0) | (1 << OCIE0A);

    sei();
}

void power_off() {
    PORT_POWER &= ~(1 << PIN_POWER);
    sleep_enable();
}

#define INTERRUPT_FREQ ((uint32_t)F_CPU / 64 / (1 << 8))

static void poll_buttons() {
    bool butt1 = (INPUT_BUTT1 & (1 << PIN_BUTT1)) == 0;
    bool butt2 = (INPUT_BUTT2 & (1 << PIN_BUTT2)) == 0;
    static int counter1 = 0;
    static int counter2 = 0;

    counter1++;
    counter1 *= butt1;
    counter2++;
    counter2 *= butt2;

    if (counter2 == INTERRUPT_FREQ*3) // 3 seconds
        power_off();

}

static volatile uint16_t local_matrix[5] = {
    0b000000000,
    0b000000000,
    0b000000000,
    0b000000000,
    0b000000000
};

static inline put_cols(uint16_t cols) {
    // sorry for the magic numbers
    uint8_t portc = (cols & 0b11111) << 1;
    uint8_t portd = (cols >> 5) & 0b000001111;
    uint8_t portcmask = 0b111110;
    uint8_t portdmask = 0b1111;

    PORTC &= ~portcmask;
    PORTC |= portc;
    PORTD &= ~portdmask;
    PORTD |= portd;
}

static inline put_rows(uint8_t rows) {
    uint8_t portdmask = 0xf0;
    uint8_t portcmask = 0x01;
    PORTC |= portcmask;
    PORTC &= ~((rows) & portcmask);
    PORTD |= portdmask;
    PORTD &= ~((rows << 3) & portdmask);
}

ISR(TIMER0_COMPA_vect){
    put_rows(0);
}

ISR(TIMER0_OVF_vect){
    poll_buttons();

    static int row = 0;

    put_cols(local_matrix[4-row]);
    put_rows(1 << row);

    row++;
    if (row == 5) row = 0;
}

uint16_t flip_9bit(uint16_t input) {
    uint16_t retval = 0;
    for (int i = 0; i < 9; i++) {
        if (input & (1 << i))
            retval |= 1 << (8-i);
    }
    return(retval);
}

void put_matrix(uint16_t matrix[5]) {
    for (int i = 0; i < 5; i++) {
        local_matrix[i] = flip_9bit(matrix[i]);
    }
}

