#pragma once

#include "gameobject.h"
using namespace std;

class PhysicsObject : public GameObject
{
    constexpr static float friction = 0.10f;

protected:
    raylib::Vector2 speed_;
    raylib::Vector2 acc_;
    float thrust = 10.0;


public:
    PhysicsObject(raylib::Vector2 initialPos, string texturePath, float initialScale, float initialRot);

    void update() override;

    void accelerate(raylib::Vector2 acc);

    void setSpeed(raylib::Vector2 speed);
};