#ifndef GRAVITY_H
#define GRAVITY_H

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <ctime>

#define G 500.0f

class Ball {
private:
    float mass;
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

public:
    Ball(float x, float y, Vector2 vel, float mass = 50000.0f, float radius = 30.0f)
        : mass(mass), radius(radius), position({x, y}), velocity(vel), acceleration({0, G}) {}

    // --- Getters ---
    float GetRadius() const;
    float GetMass() const;
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;

    // --- Physics Interface ---
    void ResetAcceleration();

    void ApplyForce(const Vector2& force);

    void Update(float dt);

    void Bounce(float floorY);

    // --- Rendering ---
    void Draw() const;
};

class Space {
private:
    std::vector<Ball> balls;

    void ApplyMutualGravity(Ball& a, Ball& b);

public:
    void AddBall(float x, float y, Vector2 velocity = {0,0});

    void Update(float dt, float screenHeight);

    void Draw() const;
};

class Grid {
private:
    float cellSize = 30.0f;

public:
    void Draw() const;
};

#endif // !GRAVITY_H
