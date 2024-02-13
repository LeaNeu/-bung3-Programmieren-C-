#include "gameobject.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

GameObject::GameObject(raylib::Vector2 initialPos, std::string texturePath, float initialScale, float initialRot)
: pos_(initialPos)
, tex_(texturePath)
, scale_(initialScale)
, rot_(initialRot)
, markedForDeletion_(false)
{}

GameObject::~GameObject()
{}

raylib::Vector2 GameObject::getOrigin() const
{
    return raylib::Vector2 {static_cast<float>(tex_.GetWidth() * scale_ / 2), static_cast<float>(tex_.GetHeight() * scale_ / 2) };
}

void GameObject::draw()
{
    // Easy version: Draw object with rotation around origin (top left)
    //tex_.Draw(pos_, rot_);

    // Slightly more advanced version: Draw object with rotation around center
    raylib::Vector2 origin = raylib::Vector2(tex_.GetWidth() * scale_ / 2, tex_.GetWidth() * scale_ / 2);
    raylib::Rectangle sourceRect = {0.0, 0.0, static_cast<float>(tex_.GetWidth()), static_cast<float>(tex_.GetHeight()) };
    raylib::Rectangle destRect = {pos_.GetX(), pos_.GetY(), static_cast<float>(tex_.GetWidth()) * scale_, static_cast<float>(tex_.GetHeight()) * scale_ };
    tex_.Draw(sourceRect, destRect, origin, rot_);
}

void GameObject::update()
{
}

void GameObject::rotate(float deg)
{
    rot_ += deg;
}

void GameObject::move(raylib::Vector2 moveVec)
{
    pos_ += moveVec;
    if(pos_.x < 0.0)
        pos_.x = GetScreenWidth();
    else if(pos_.x > GetScreenWidth())
        pos_.x = 0.0;
    if(pos_.y < 0.0)
        pos_.y = GetScreenHeight();
    else if(pos_.y > GetScreenHeight())
        pos_.y = 0.0;
}

float GameObject::getRotation() const
{
    return rot_;
}

raylib::Vector2 GameObject::getPosition() const
{
    return pos_;
}

void GameObject::markForDeletion()
{
    markedForDeletion_ = true;
}

bool GameObject::isMarkedForDeletion() const
{
    return markedForDeletion_;
}

int GameObject::getWidth() const {
    return tex_.width;
}

void GameObject::handleCollision(std::shared_ptr<GameObject>){

}