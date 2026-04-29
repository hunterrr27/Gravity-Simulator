#include "gravity.h"

class Ball {
public:
    // characteristics
    float mass = 50000.0f;
    Vector2 velocity = { 0.0f, 0.0f };
    float radius = 30.0f;
    Vector2 acceleration = { 0, G };

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
        this->velocity.x += acceleration.x * deltaTime;
        this->velocity.y += acceleration.y * deltaTime;
        this->x += this->velocity.x * deltaTime;
        this->y += this->velocity.y * deltaTime;
    }
    void Bounce(float floorY) {
        y = floorY - radius;
        velocity.y *= -0.9f;
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
        for (Ball &b : balls) {
            b.acceleration = { 0, G };
        }
        // gravity update loop
        for (size_t i = 0; i < balls.size(); i++) {
            for (size_t j = i + 1; j < balls.size(); j++) {
                // logic for ball i pulling on ball j AND ball j pulling on ball i
                float dx = balls[j].x - balls[i].x;
                float dy = balls[j].y - balls[i].y;
                float d = sqrt(pow(dx, 2) + pow(dy, 2));
                // set min limit for d so we never divide by 0
                d = fmaxf(d, 30.0f);

                Vector2 direction = { dx / d, dy / d };
                float force = (G * balls[i].mass * balls[j].mass) / pow(d, 2);
                balls[i].acceleration.x += direction.x * force / balls[i].mass;
                balls[i].acceleration.y += direction.y * force / balls[i].mass;
                balls[j].acceleration.x += -direction.x * force / balls[j].mass;
                balls[j].acceleration.y += -direction.y * force / balls[j].mass;
            }
        }

        // individual movement and boundaries
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