#pragma once

#include <raylib-cpp.hpp>

#include "gameobject.h"

class Asteroid : public GameObject
{
public:
    enum Size
    {
        SMALL = 0,
        MEDIUM,
        BIG
    };

private:
    inline static const std::string texturePath_ = "./resources/ohmsteroid.png";
    Size size_;
    raylib::Vector2 velocity_;

    void updateScale();

public:
    Asteroid(raylib::Vector2 initialPos, float initialRot, Size initialSize, raylib::Vector2 initialVelocity);

    void update() override;

    Size getSize() const;

    void handleCollision(std::shared_ptr<GameObject> other) override;
};
