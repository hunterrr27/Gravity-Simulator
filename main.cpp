#include "gravity.h"

class Ball {
private:
    float mass;
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

public:
    Ball(float x, float y, float mass = 50000.0f, float radius = 30.0f)
        : mass(mass), radius(radius), position({x, y}), velocity({0, 0}), acceleration({0, G}) {}

    // --- Getters ---
    float GetRadius() const { return radius; }
    float GetMass() const { return mass; }
    Vector2 GetPosition() const { return position; }
    Vector2 GetVelocity() const { return velocity; }

    // --- Physics Interface ---
    void ResetAcceleration() {
        acceleration = {0, G};
    }

    void ApplyForce(const Vector2& force) {
        acceleration.x += force.x / mass;
        acceleration.y += force.y / mass;
    }

    void Update(float dt) {
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
    }

    void Bounce(float floorY) {
        position.y = floorY - radius;
        velocity.y *= -0.9f;
    }

    // --- Rendering ---
    void Draw() const {
        DrawCircleV(position, radius, BLACK);
    }
};

class Space {
private:
    std::vector<Ball> balls;

    void ApplyMutualGravity(Ball& a, Ball& b) {
        Vector2 posA = a.GetPosition();
        Vector2 posB = b.GetPosition();

        float dx = posB.x - posA.x;
        float dy = posB.y - posA.y;
        float dist = sqrtf(dx * dx + dy * dy);
        dist = fmaxf(dist, 30.0f);

        Vector2 direction = { dx / dist, dy / dist };

        float forceMagnitude =
            (G * a.GetMass() * b.GetMass()) / (dist * dist);

        Vector2 force = {
            direction.x * forceMagnitude,
            direction.y * forceMagnitude
        };

        a.ApplyForce(force);
        b.ApplyForce({ -force.x, -force.y });
    }

public:
    void AddBall(float x, float y) {
        balls.emplace_back(x, y);
    }

    void Update(float dt, float screenHeight) {
        // Reset accelerations
        for (auto& b : balls)
            b.ResetAcceleration();

        // Apply mutual gravity
        for (size_t i = 0; i < balls.size(); i++) {
            for (size_t j = i + 1; j < balls.size(); j++) {
                ApplyMutualGravity(balls[i], balls[j]);
            }
        }

        // Update movement + floor collision
        for (auto& b : balls) {
            b.Update(dt);

            if (b.GetPosition().y + b.GetRadius() >= screenHeight) {
                b.Bounce(screenHeight);
            }
        }
    }

    void Draw() const {
        for (const auto& b : balls)
            b.Draw();
    }
};

int main() {
    const float screenWidth = 1200;
    const float screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");
    SetTargetFPS(60);

    Space space;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 m = GetMousePosition();
            space.AddBall(m.x, m.y);
        }

        space.Update(dt, screenHeight);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        space.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
