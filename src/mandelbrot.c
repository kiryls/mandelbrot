#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"
#include "include/raymath.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define ITERATIONS 100

float zoom = 1.5;
Vector2 zoom_center = {.y = 0.0, .x = 0.0};

Vector2 f(Vector2 z, Vector2 c) {
    Vector2 z_squared = {.x = (z.x*z.x - z.y*z.y), .y = (2*z.x*z.y)};
    return Vector2Add(z_squared, c);
}

Vector2 map_c(int i, int j) {
    float r = zoom_center.y - (1.5)/zoom + (float)i*3/(SCREEN_H * zoom);
    float c = zoom_center.x - (3.0)/zoom + (float)j*4/(SCREEN_W * zoom);

    return (Vector2){.x = c, .y = r};
}

Color map_color(float value) {
    if (value < 2.0) {
        return BLACK;
    }
    
    return ColorFromHSV((value - 2) * 360, 1.0, 1.0);
}

int main(int argc, char *argv[]) {

    Color pixels[SCREEN_H][SCREEN_W];

    InitWindow(SCREEN_W, SCREEN_H, "Mandelbrot");
    SetTargetFPS(1);

    while (!WindowShouldClose()) {
        for(int i = 0; i < GetScreenHeight(); ++i) {
            for(int j = 0; j < GetScreenWidth(); ++j) {
                Vector2 z = Vector2Zero();
                Vector2 c = map_c(i, j);
                int k = ITERATIONS;
                while(Vector2Length(z) <= 2.0 && k > 0) {
                    z = f(z, c);
                    k--;
                }
                pixels[i][j] = map_color(Vector2Length(z));
            }
        }

        BeginDrawing();
        for(int i = 0; i < 480; ++i) {
            for(int j = 0; j < 640; ++j) {
                DrawPixel(j, i, pixels[i][j]);
            }
        }
        DrawLineV(map_c(0, SCREEN_W/2), map_c(SCREEN_H, SCREEN_W/2), RED);
        EndDrawing();
    } 

    return EXIT_SUCCESS;
}
