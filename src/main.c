#include <stdint.h>
#include "hardware.h"
#include "font.h"
#include "counters.h"


int main(void) {
    hardware_init();


    int i = 198;

    while(1) {
        display_integer(i);

        enum events events = get_and_clear_button_events();

        if (events & EVENT_LEFT_BUTTON) {
            if (i >= 200) {
                i -= 10;
            } else {
                i--;
            }
        } if (events & EVENT_RIGHT_BUTTON) {
            if (i >= 200) {
                i += 10;
            } else {
                i++;
            }
        } if (events & EVENT_BOTH_BUTTONS) {
            i = 0;
        }

    }
}


