#include "gravity.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    double originX = screenWidth / 2;
    double originY = screenHeight / 2;

    int radius = 30;

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(originX, originY, radius, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}