#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

int main(void) {
    clock_prescale_set(clock_div_1);

    DDRC |= _BV(DDC1);
    DDRD |= _BV(DDD6);
    DDRB |= _BV(DDB6);
    PORTD &= ~_BV(PORTD7);
    PORTB |= _BV(PORTB6);


    while(1) {
        PORTC |= _BV(PORTC1);

        _delay_ms(500);

        PORTC &= ~_BV(PORTC1);

        _delay_ms(500);
    }
}
