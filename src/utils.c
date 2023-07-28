#include <stdbool.h>
#include <stdint.h>

void set_pixel(uint16_t matrix[5], int x, int y, bool state) {
    uint16_t line = 1 << (8 - x);
    if (state)
        matrix[y] |= line;
    else
        matrix[y] &= ~line;
}
