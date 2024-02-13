#pragma once

#include "physicsobject.h"

#include <list>

class Spaceship : public PhysicsObject
{
private:
    inline static const std::string texturePath_ = "./resources/spaceship.png";
    const float movementSpeed_ = 4.0;
    const float rotationSpeed_ = 4.5;
    const int maxHealth_ = 100;

    int health_;

public:
    Spaceship(raylib::Vector2 initialPos);

    void update() override;

    int getHealth() const;

    void setHealth(int);

    void handleCollision(std::shared_ptr<GameObject> other);
};