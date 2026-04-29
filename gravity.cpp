#include "gravity.h"

int main(void) {
    const float screenWidth = 1200;
    const float screenHeight = 800;

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
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV({ball.x, ball.y}, ball.radius, BLACK);

        if (ball.y + ball.radius >= screenHeight) {
            ball.velocity *= -0.9f;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ball.x = mouse.x;
            ball.y = mouse.y;
            ball.velocity = 0.0f;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}