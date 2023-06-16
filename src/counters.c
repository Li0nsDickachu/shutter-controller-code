#include "font.h"
#include "hardware.h"
#include "Assert.h"

void display_integer (int number) {
    Assert(number >= -1, "Invalid value, integer < -1");
    Assert(number <= 999, "Invalid value, integer > 999");

    uint16_t matrix[5] = {};

    if (number == -1) {
        int offset = put_character(character_infinity[0], 0, matrix);
        put_character(character_infinity[1], offset -1, matrix);
    } else if (number < 100) {
        put_character(wide_font['0' + number%10], 5, matrix);
        if (number >= 10) {
            put_character(wide_font['0' + number/10], 0, matrix);
        }
    } else if (number < 200) {
        put_character(narrow_font['0' + number%10], 6, matrix);
        put_character(narrow_font['0' + (number/10) % 10], 2, matrix);
        put_character(narrow_font['1'], -2, matrix); // only 100-199
    } else {
        Assert(number%10 == 0, "Integer > 200 can only increase in steps of 10");

        put_character(character_super_narrow_zero, 8, matrix);
        put_character(narrow_font['0' + (number/10) % 10], 4, matrix);
        put_character(narrow_font['0' + (number/100) % 10], 0, matrix);
    }

    put_matrix(matrix);
}
