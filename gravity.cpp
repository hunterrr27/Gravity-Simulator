#include "gravity.h"

// --- Ball::Getters ---
float Ball::GetRadius() const { return radius; }
float Ball::GetMass() const { return mass; }
Vector2 Ball::GetPosition() const { return position; }
Vector2 Ball::GetVelocity() const { return velocity; }

// --- Physics Interface ---
void Ball::ResetAcceleration() {
    acceleration = {0, G};
}

void Ball::ApplyForce(const Vector2& force) {
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
}

void Ball::Update(float dt) {
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Ball::Bounce(float floorY) {
    position.y = floorY - radius;
    velocity.y *= -0.9f;
}

// --- Rendering ---
void Ball::Draw() const {
    DrawCircleV(position, radius, RAYWHITE);
}

// ---
// --- Space Class methods ---
// ---
void Space::ApplyMutualGravity(Ball& a, Ball& b) {
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

void Space::AddBall(float x, float y, Vector2 velocity) {
    balls.emplace_back(x, y, velocity);
}

void Space::Update(float dt, float screenHeight) {
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

void Space::Draw() const {
    for (const auto& b : balls)
        b.Draw();
}

// ---
// --- Grid Class Methods
// ---
void Grid::Draw() const {
    DrawGrid(10, 0.5);
}