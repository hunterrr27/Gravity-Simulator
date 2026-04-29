#include "gravity.h"

class Ball {
public:
    // characteristics
    float mass = 1.0f;
    float velocity = 0.0f;
    float radius = 30.0f;

    // position
    float x = 0.0f;
    float y = 0.0f;

    // constructor
    Ball(float startX, float startY) : x(startX), y(startY) {}

    // methods
    // draw method
    void Draw() {
        DrawCircleV({this->x, this->y}, this->radius, BLACK);
    }
    void Update(float deltaTime) {
        this->velocity += G * deltaTime;
        this->y += this->velocity * deltaTime;
    }
    void Bounce(float floorY) {
        y = floorY - radius;
        velocity *= -0.9f;
    }
    float GetY() { return this->y; }
    float GetRadius() { return this->radius; }

};

class Space {
private:
    std::vector<Ball> balls;

public:
    void AddBall(float x, float y) {
        balls.push_back(Ball(x, y));
    }
    void Update(float deltaTime, float screenHeight) {
        // gravity update loop
        for (Ball &b : balls) {
            b.Update(deltaTime);

            if (b.GetY() + b.GetRadius() >= screenHeight) {
                b.Bounce(screenHeight);
            }
        }
    }
    void Draw() {
        for (Ball &b : balls) {
            b.Draw();
        }
    }
    

};

int main(void) {
    Space mySpace;
    const float screenWidth = 1200;
    const float screenHeight = 800;

    // newtons law of universal gravitation
    // const force = (G * m1 * m2) / (r * r);

    float originX = screenWidth / 2;
    float originY = screenHeight / 2;

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        float deltaTime = GetFrameTime();

        mySpace.Update(deltaTime, screenHeight);
        mySpace.Draw();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            mySpace.AddBall(mouse.x, mouse.y);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}