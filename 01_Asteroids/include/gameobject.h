#pragma once

#include <raylib-cpp.hpp>
#include <memory>

class GameObject
{
private:
    raylib::Texture tex_;
    bool markedForDeletion_;

protected:
    float rot_;
    raylib::Vector2 pos_;
    float scale_;


public:
    raylib::Vector2 getOrigin() const;

    GameObject(raylib::Vector2 initialPos, std::string texturePath, float initialScale, float initialRot);

    virtual ~GameObject();

    virtual void update();

    void draw();

    virtual void rotate(float deg);

    virtual void move(raylib::Vector2 moveVec);

    void markForDeletion();

    bool isMarkedForDeletion() const;

    float getRotation() const;

    raylib::Vector2 getPosition() const;

    int getWidth() const;


    virtual void handleCollision(std::shared_ptr<GameObject>);
};