#include <stdio.h>
#include "font.h"
#include "hardware.h"
#include "counters.h"
#include "Assert.h"

void alter_value(int *seconds_or_int, int *ms, int min, int max, enum value_type type, int direction) {
    (void)ms;
    if (type == VALUE_INT) {
        *seconds_or_int = alter_integer(min, max, direction, *seconds_or_int);
    }
}

int alter_integer(int min, int max, int direction, int value) {
    Assert(direction == UP || direction == DOWN, "Invalid direction");

    if (value <= min && direction == DOWN) {
        return min;
    } else if (value + direction <= 200) {
        return value + direction;
    } else if (value + direction*10 <= max) {
        return value + direction*10;
    } else {
        return max;
    }
}

void display_integer(int number) {
    Assert(number >= -1, "Invalid value, integer < -1");
    Assert(number <= 990, "Invalid value, integer > 990");

    uint16_t matrix[5] = {};

    if (number == -1) {
        int offset = put_character(&character_infinity[0], 0, matrix);
        put_character(&character_infinity[1], offset -1, matrix);
    } else if (number < 100) {
        put_character(&wide_font['0' + number%10], 5, matrix);
        if (number >= 10) {
            put_character(&wide_font['0' + number/10], 0, matrix);
        }
    } else if (number < 200) {
        put_character(&narrow_font['0' + number%10], 6, matrix);
        put_character(&narrow_font['0' + (number/10) % 10], 2, matrix);
        put_character(&narrow_font['1'], -2, matrix); // only 100-199
    } else {
        Assert(number%10 == 0, "Integer > 200 can only increase in steps of 10");

        put_character(&character_super_narrow_zero, 8, matrix);
        put_character(&narrow_font['0' + (number/10) % 10], 4, matrix);
        put_character(&narrow_font['0' + (number/100) % 10], 0, matrix);
    }

    put_matrix(matrix);
}

void alter_time(int *seconds, int *ms, int min, int max, int direction, enum value_type type) {
    (void)min;
    (void)max;
    if (type == VALUE_TIME_FRACTIONAL_SECONDS) {
        if (seconds == 0) {
            if (direction == DOWN) {
                if (*ms == 10) return; // minimum time value with fractional seconds
                else if (*ms + direction*10 <= 1000) {
                    *ms += direction * 10;
                    return;                   
                } else {
                    *ms = 0;
                    *seconds = 1;
                    return;
                }
            }
        }
    }

    Assert(*ms == 0, "This part shouldn't be reachable without ms being 0");

    //if () {

    //}
}

void display_time(int seconds, int ms) {
    uint16_t matrix[5] = {};

    if (seconds == 0) {
        Assert(ms % 10 == 0, "Can't display higher precision than 10ms");
        put_character(&narrow_font['.'], 0, matrix);
        put_character(&narrow_font['0' + (ms/10) % 10], 6, matrix);
        put_character(&narrow_font['0' + (ms/100) % 10], 2, matrix);
    } else if (seconds < 10) {
        Assert(ms % 100 == 0, "Can't display higher precision than 100ms");
        put_character(&narrow_font['0' + (ms/100) % 10], 6, matrix);
        put_character(&narrow_font['.'], 4, matrix);
        put_character(&narrow_font['0' + seconds], 0, matrix);
    } else if (seconds >= 10 && seconds < 60) {
        Assert(ms == 0, "Can't display ms when seconds > 9");
        put_character(&wide_font[':'], 0, matrix);
        put_character(&narrow_font['0' + seconds % 10], 6, matrix);
        put_character(&narrow_font['0' + (seconds/10) % 10], 2, matrix);
    } else if (seconds >= 60 && seconds < 60*9) {
        Assert(ms == 0, "Can't display ms when seconds > 9");
        Assert(seconds % 10 == 0, "Can't display higher precision than 10 seconds");

        put_character(&narrow_font['0' + (seconds/60)], 0, matrix);
        put_character(&wide_font[':'], 4, matrix);
        put_character(&narrow_font['0' + (seconds % 60) / 10], 6, matrix);
    } else if (seconds >= 60*9 && seconds < 60*60) {
        Assert(ms == 0, "Can't display ms when seconds > 9");
        Assert(seconds % 60 == 0, "Can't display higher precision than 60 seconds");

        put_character(&narrow_font['0' + (seconds / 60 / 10)], 0, matrix);
        put_character(&narrow_font['0' + (seconds / 60) % 10], 4, matrix);
        put_character(&wide_font[':'], 8, matrix);
    } else {
        char buffer[101] = {};

        snprintf(buffer, sizeof(buffer) - 1, "Can't display %is and %ims", seconds, ms);

        Assert(0, buffer);
    }

    put_matrix(matrix);
}
