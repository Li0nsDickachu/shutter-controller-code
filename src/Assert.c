#include "font.h"
#include "hardware.h"
#include <string.h>
#include <stdio.h>

void Assert(bool condition, char* debug_message) {
    if (!condition) {
#ifdef IN_SIMULATOR
        printf("Assertion failed: %s\n", debug_message);
#endif
        char prefix[] = "Assertion: ";
        char full_message[strlen(prefix) + strlen(debug_message) + 1];

        strcpy(full_message, prefix);
        strcpy(full_message + strlen(prefix), debug_message);


        while(1) {
            int x_coord = 1;
            int start_x = 9;
            while (x_coord != 0) {
                uint16_t matrix[5] = {};
                x_coord = put_string(full_message, start_x, wide_font, matrix);
                put_matrix(matrix);
                start_x--;
                delay_ms(100);
            }
        }
    }
}

