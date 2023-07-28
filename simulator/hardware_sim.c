#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "raylib.h"
#include <pthread.h>
#include "hardware.h"

volatile static enum events occurred_events;
_Atomic bool events_busy = false;

volatile static uint16_t global_matrix[5] = {};
pthread_mutex_t mutex;

uint8_t pgm_read_byte(const uint8_t *address) {
    return *address;
}

void shutter_button(bool dir) {
    if (dir == BUTTON_DOWN) {
        printf("Shutter button down\n");
    } else {
        printf("Shutter button up\n");
    }
}

static void poll_buttons(bool butt2, bool butt1) {
    static bool prev_butt1 = 0;
    static bool prev_butt2 = 0;
    static bool both_pressed = 0;

    if (butt1 && butt2)
        both_pressed = 1;

    pthread_mutex_lock(&mutex);
    if (butt1 == 1 && prev_butt1 == 0) {
        occurred_events |= EVENT_RIGHT_BUTTON_DOWN;
    } else if (butt1 == 0 && prev_butt1 == 1) {
        if (!both_pressed) {
            occurred_events |= EVENT_RIGHT_BUTTON_UP;
        } else if (butt2 == 0) {
            occurred_events |= EVENT_BOTH_BUTTONS_UP;
            both_pressed = 0;
        }
    }

    if (butt2 == 1 && prev_butt2 == 0) {
        occurred_events |= EVENT_LEFT_BUTTON_DOWN;
    } else if (butt2 == 0 && prev_butt2 == 1) {
        if (!both_pressed)
            occurred_events |= EVENT_LEFT_BUTTON_UP;
        else if (butt1 == 0) {
            occurred_events |= EVENT_BOTH_BUTTONS_UP;
            both_pressed = 0;
        }
    }
    pthread_mutex_unlock(&mutex);


    prev_butt1 = butt1;
    prev_butt2 = butt2;
}

void *raylib_thread(void *vargp) {
    const int matrix_width = 9;
    const int matrix_heigth = 5;
    const int screenWidth = 500;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "sim");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGREEN);

        for (int y = 0; y < matrix_heigth; y++) {
            for (int x = 0; x < matrix_width; x++) {
                Rectangle rec;
                DrawRectanglePro((Rectangle){x*50 + 50, y*50 + 50, 40, 20}, (Vector2){20, 10}, -45, GRAY);
                DrawRectanglePro((Rectangle){x*50 + 50, y*50 + 50, 20, 20}, (Vector2){10, 10}, -45, LIGHTGRAY);
            }
        }

        for (int y = 0; y < matrix_heigth; y++) {
            for (int x = 0; x < matrix_width; x++) {
                if (global_matrix[y] & 1 << (matrix_width - 1 - x)) {
                    for (int i = 70; i > 0; i-= 2)
                        DrawCircleV((Vector2){x*50 + 50, y*50 + 50}, i, (Color){255, 30, 30, 3});
                    for (int i = 20; i > 0; i--)
                        DrawCircleV((Vector2){x*50 + 50, y*50 + 50}, i, (Color){255, 82+(30-i), 55, 30});
                    for (int i = 12; i > 0; i--)
                        DrawCircleV((Vector2){x*50 + 50, y*50 + 50}, i, (Color){255, 255, 255, 20});
                }
            }
        }

        Color left = BLACK;
        Color right = BLACK;
        bool left_down = (IsKeyDown(KEY_F));
        bool right_down = (IsKeyDown(KEY_J));
        if (left_down) left = GRAY;
        if (right_down) right = GRAY;

        poll_buttons(left_down, right_down);

        DrawRectangle(20, 350, 60, 60, left);
        DrawRectangle(screenWidth - 20 - 60, 350, 60, 60, right);

        EndDrawing();

    }

    CloseWindow();
}

void put_matrix(uint16_t matrix[5]) {
    for (int i = 0; i < 5; i++) {
        global_matrix[i] = matrix[i];
    }
}

void hardware_init() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, raylib_thread, NULL);
}

void delay_ms(double ms) {
    sleep((uint64_t)(ms * 1000));
}

enum events get_and_clear_button_events() {
    pthread_mutex_lock(&mutex);

    enum events retval = occurred_events;
    occurred_events = 0;

    pthread_mutex_unlock(&mutex);

    return retval;
}
