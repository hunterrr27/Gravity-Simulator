#ifndef GRAVITY_H
#define GRAVITY_H

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <time.h>

#define G 500.0f

class Ball {
public:
    // characteristics
    float mass = 1.0f;
    float velocity = 0.0f;
    float radius = 30.0f;

    // position
    float x = 0.0f;
    float y = 0.0f;

};

#endif // !GRAVITY_H
