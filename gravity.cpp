#include "gravity.h"

int main(void) {
    const float screenWidth = 800;
    const float screenHeight = 600;

    float originX = screenWidth / 2;
    float originY = screenHeight / 2;

    float radius = 30;

    Ball ball;
    ball.radius = radius;
    ball.x = originX;
    ball.y = originY;
    ball.velocity = 0.0f;

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        ball.velocity += G * deltaTime;
        ball.y += ball.velocity * deltaTime;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV({ball.x, ball.y}, ball.radius, BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}