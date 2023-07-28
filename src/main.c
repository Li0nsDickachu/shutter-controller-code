#include <stdint.h>
#include <stddef.h>
#include "hardware.h"
#include "font.h"
#include "counters.h"

typedef struct state {
    struct state (*screen)(struct state);
    int current_profile;
} state_t;

state_t screen_main(state_t state);
state_t screen_settings(state_t state);

state_t screen_main(state_t state) {
    while(1) {
        uint16_t matrix[6] = {};
        put_character(&wide_font['P'], 0, matrix);

        put_character(&wide_font['0' + state.current_profile], 5, matrix);

        enum events events = get_and_clear_button_events();

        if (events & EVENT_BOTH_BUTTONS_UP) {
            state.screen = screen_settings;
            return state;
        }
        if (events & EVENT_RIGHT_BUTTON_UP) {
            state.current_profile += 1;
            state.current_profile %= 10;
        }
        if (events & EVENT_LEFT_BUTTON_UP) {
            shutter_button(BUTTON_DOWN);
            delay_ms(100);
            shutter_button(BUTTON_UP);
        }

        put_matrix(matrix);
    }
}

void ns_screen_modify_setting(int *seconds_or_int, int *ms, int min, int max, enum value_type type) {
    display_integer(*seconds_or_int);
    (void)ms;
    (void)type;

    while (1) {
        enum events events = get_and_clear_button_events();

        if (events & EVENT_RIGHT_BUTTON_UP) {
            *seconds_or_int = alter_integer(min, max, UP, *seconds_or_int);
            display_integer(*seconds_or_int);
        }
        if (events & EVENT_LEFT_BUTTON_UP) {
            *seconds_or_int = alter_integer(min, max, DOWN, *seconds_or_int);
            display_integer(*seconds_or_int);
        }
        if (events & EVENT_BOTH_BUTTONS_UP) {
            return;
        }
    }
}

state_t screen_settings(state_t state) {
    int i = 0;
    int x = 0;

    char* settings[] = {"Exposure time", "Delay before first picture", "Amount of pictures", "Repeat delay", "Brightness during exposure", "Master brightness", "Focus time before taking picture"};
    int settings_ind = 0;
    int settings_size = sizeof(settings) / sizeof(settings[0]);

    while(1) {
        ////////////////////////////////////
        /// Rendering of settings string ///
        ////////////////////////////////////
        uint16_t matrix[6] = {};

        if (i > 10 && (i % 2 == 0)) {
            x--;
        }

        int end_of_string = put_string(settings[settings_ind], x, wide_font, matrix);

        if (end_of_string == -3)
            x = 9;

        put_matrix(matrix);
        ////////////////////////////////////


        //////////////////////
        /// Input handling ///
        //////////////////////
        enum events events = get_and_clear_button_events();

        if (events & EVENT_RIGHT_BUTTON_UP) {
            settings_ind++;
            if (settings_ind >= settings_size) {
                state.screen = screen_main;
                return state;
            } else {
                x = 0;
                i = 0;
            }
        } else if (events & EVENT_LEFT_BUTTON_UP) {
            int value = 0;
            ns_screen_modify_setting(&value, NULL, INFINITY, 990, VALUE_INT);
        } else if (events & EVENT_BOTH_BUTTONS_UP) {
            state.screen = screen_main;
            return state;
        }
        //////////////////////

        delay_ms(100);
        i++;
    }
    return state;
}

int main(void) {
    hardware_init();
    int pos = 0;
    while (1) {
        enum events events = get_and_clear_button_events();

        if (events & EVENT_LEFT_BUTTON_DOWN) {
            pos++;
        } if (events & EVENT_RIGHT_BUTTON_DOWN) {
            pos--;
        }

        uint16_t matrix[6] = {};
        matrix[3] = 1 << pos;
        put_matrix(matrix);
    }

    state_t current_state = {
        screen_main,
        0
    };

    while (1) {
        current_state = current_state.screen(current_state);
    }
}


