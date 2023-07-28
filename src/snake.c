#include <stdint.h>
#include "hardware.h"
#include "utils.h"

void snake() {
    int pos = 0;
    while (1) {
        enum events events = get_and_clear_button_events();

        if (events & EVENT_LEFT_BUTTON_DOWN) {
            pos--;
            if (pos == -1)
                return;
        } if (events & EVENT_RIGHT_BUTTON_DOWN) {
            pos++;
            if (pos == 9 * 5)
                return;
        }

        uint16_t matrix[6] = {};

        set_pixel(matrix, pos % 9, pos / 9, 1);

        put_matrix(matrix);

    }
}
