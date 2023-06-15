#include <stdint.h>
#include "hardware.h"
#include "font.h"


int main(void) {
    hardware_init();


    int i = 9;
    while(1) {
        uint16_t matrix[5] = {};

        //put_string("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz", i, wide_font, matrix);

        put_matrix(matrix);

        //delay_ms(400);

        i--;

        enum events events = get_and_clear_button_events();

        if (events & EVENT_LEFT_BUTTON) {
            uint16_t matrix2[5] = {};
            put_string("Left", 0, wide_font, matrix2);
            put_matrix(matrix2);

            delay_ms(100);
        } if (events & EVENT_RIGHT_BUTTON) {
            uint16_t matrix2[5] = {};
            put_string("Right", 0, wide_font, matrix2);
            put_matrix(matrix2);

            delay_ms(100);
        } if (events & EVENT_BOTH_BUTTONS) {
            uint16_t matrix2[5] = {};
            put_string("Both", 0, wide_font, matrix2);
            put_matrix(matrix2);

            delay_ms(100);
        }

    }
}


