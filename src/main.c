#include <stdint.h>
#include "hardware.h"
#include "font.h"


int main(void) {
    hardware_init();


    int i = 9;
    while(1) {
        uint16_t matrix[5] = {};

        put_string("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz", i, wide_font, matrix);

        put_matrix(matrix);

        delay_ms(400);

        i--;
    }
}


