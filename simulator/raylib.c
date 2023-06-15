#include "raylib.h"
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

volatile static uint16_t matrix[5] = {};

void *raylib_thread(void *vargp) {
    const int matrix_width = 9;
    const int matrix_heigth = 5;
    const int screenWidth = 500;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Camera shutter controller");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGREEN);

        for (int y = 0; y < matrix_heigth; y++) {
            for (int x = 0; x < matrix_width; x++) {
                Rectangle rec;
                DrawRectanglePro((Rectangle){x*50 + 50, y*50 + 50, 40, 20}, (Vector2){20, 10}, -45, GRAY);
            }
        }

        for (int y = 0; y < matrix_heigth; y++) {
            for (int x = 0; x < matrix_width; x++) {
                if (matrix[y] & 1 << (matrix_width - x)) {
                    for (int i = 70; i > 0; i-= 2)
                        DrawCircleV((Vector2){x*50 + 50, y*50 + 50}, i, (Color){255, 30, 30, 10});
                    for (int i = 30; i > 0; i--)
                        DrawCircleV((Vector2){x*50 + 50, y*50 + 50}, i, (Color){255, 82+(30-i), 35, 10});
                }
            }
        }

        Color left = BLACK;
        Color right = BLACK;
        if (IsKeyDown(KEY_F)) left = GRAY;
        if (IsKeyDown(KEY_J)) right = GRAY;

        DrawRectangle(20, 350, 60, 60, left);
        DrawRectangle(screenWidth - 20 - 60, 350, 60, 60, right);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}

int main(void) {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, raylib_thread, NULL);
    while (1) {
        matrix[0] ^= 0b100000;
        matrix[1] ^= 0b100000;
        matrix[2] ^= 0b100000;
        matrix[3] ^= 0b100010;
        matrix[4] ^= 0b011100;
        usleep(1000000);
    }
    pthread_join(thread_id, NULL);
}

