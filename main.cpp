#include "gravity.h"

int main() {
    const float screenWidth = 1200;
    const float screenHeight = 800;

    

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");
    SetTargetFPS(60);

    Space space;
    Grid grid;

    space.AddBall(600, 200, {177.0f, 0});
    space.AddBall(600, 600, {-177.0f, 0});

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        space.Update(dt, screenHeight);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            space.AddBall(mouse.x, mouse.y, {0, 0});
        }

        BeginDrawing();
        ClearBackground(BLACK);
        grid.Draw();
        space.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
