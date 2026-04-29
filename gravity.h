#ifndef GRAVITY_H
#define GRAVITY_H

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"

#define ACCELERATION 9.81

class Ball {
    // characteristics
    int mass;
    int velocity;
    int radius;

    // position
    double x;
    double y;

};

#endif // !GRAVITY_H
