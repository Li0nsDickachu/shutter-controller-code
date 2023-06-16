#include <stdint.h>
#include "hardware.h"
#include "font.h"
#include "counters.h"


int main(void) {
    hardware_init();


    int i = 0;
    


    while(1) {
        display_integer(i);

        enum events events = get_and_clear_button_events();

        if (events & EVENT_LEFT_BUTTON) {
            i--;
        } if (events & EVENT_RIGHT_BUTTON) {
            i++;
        } if (events & EVENT_BOTH_BUTTONS) {
            i = 0;
        }

    }
}


