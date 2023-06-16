#include "font.h"
#include "hardware.h"
#include "Assert.h"

void display_integer (int number) {
    Assert(number >= -1, "Invalid value, integer < -1");

    uint16_t matrix[5] = {};

    if (number == -1) {
        int offset = put_character(character_infinity[0], 0, matrix);
        put_character(character_infinity[1], offset -1, matrix);
    } else if (number < 100) {
        put_character(wide_font['0' + number%10], 5, matrix);
        if (number >= 10) {
            put_character(wide_font['0' + number/10], 0, matrix);
        }
    } else {
    }

    put_matrix(matrix);
}
