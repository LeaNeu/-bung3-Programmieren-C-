#include "spaceship.h"
#include "physicsobject.h"
#include "asteroid.h"
using namespace std;

Spaceship::Spaceship(raylib::Vector2 initialPos)
: PhysicsObject(initialPos, texturePath_, 1.0, 0.0)
, health_(maxHealth_)
{
    speed_=0;
}

void Spaceship::update()
{
    if(IsKeyDown(KEY_W))
        accelerate(raylib::Vector2{0.f, -thrust}.Rotate(DEG2RAD * rot_));
    if(IsKeyDown(KEY_A))
        rotate(-rotationSpeed_);
    if(IsKeyDown(KEY_D))
        rotate(rotationSpeed_);
    if(IsKeyDown(KEY_S))
        accelerate(raylib::Vector2{0.f, thrust}.Rotate(DEG2RAD * rot_));

    PhysicsObject::update();
}

int Spaceship::getHealth() const
{
    return health_;
}


void Spaceship::handleCollision(std::shared_ptr<GameObject> other) {
    std::shared_ptr<Asteroid> asteroid = std::dynamic_pointer_cast<Asteroid>(other);

    if(asteroid != nullptr){
        if(health_ - 5> 0){
            health_ = health_ -5;
        }else{
            health_ = 0;
        }
        asteroid->markForDeletion();
    }
}

void Spaceship::setHealth(int health) {
    if(health > 0 && health < 101){
        health_ = health;
    }
}

