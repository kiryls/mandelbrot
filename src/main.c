#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

int main(int argc, char *argv[]) {
    InitWindow(640, 480, "Mandelbrot");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV((Vector2){.y = (float)GetScreenHeight()/2, .x = (float)GetScreenWidth()/2}, 42, BLACK);
        EndDrawing();
    }
    return EXIT_SUCCESS;
}
