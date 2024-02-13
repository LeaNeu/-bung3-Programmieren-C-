#include "physicsobject.h"
#include <iostream>
using namespace std;


PhysicsObject::PhysicsObject(raylib::Vector2 initialPos, string texturePath, float initialScale, float initialRot)
        : GameObject(initialPos, texturePath, initialScale, initialRot)
        ,speed_(5)
        {

}

void PhysicsObject::update() {
    float dt = 1.0f / 60.0f;
    speed_ = Vector2Add(speed_, Vector2Scale(acc_, dt)); // Beschleunigung anwenden
    speed_ = Vector2Subtract(speed_, Vector2Scale(speed_, friction * dt)); // Reibung anwenden
    move(speed_);
    acc_ = 0 ; // Beschleunigung zurücksetzen
}

void PhysicsObject::accelerate(raylib::Vector2 acc){
    acc_ = acc;
}


void PhysicsObject::setSpeed(raylib::Vector2 speed){
    speed_= speed;
};