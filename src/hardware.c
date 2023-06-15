#include <stdio.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay_ms(double ms) {
    _delay_ms(ms);
}

void hardware_init() {
    clock_prescale_set(clock_div_1);

    DDRC = 0b00111111;
    DDRD = 0b11111111;

    TCNT0 = 0;
    OCR0A = 255;
    TCCR0A = 0x0;
    TCCR0B |= (1<<CS00) | (1<<CS01);
    TIMSK0 |= (1<<TOIE0) | (1 << OCIE0A);

    sei();
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
    static int row = 0;

    put_cols(local_matrix[4-row]);
    put_rows(1 << row);

    row++;
    if (row == 5) row = 0;

    TCNT0 = 0;
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

