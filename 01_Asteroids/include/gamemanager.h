#pragma once

#include <list>
#include <memory>

#include "gameobject.h"
#include "spaceship.h"
#include "asteroid.h"
#include "projectile.h"

class GameManager
{
    using GameObjectContainer = std::list<std::shared_ptr<GameObject>>;

private:
    int score_;
    bool gameOver_ = false;

    GameObjectContainer objects_;
    std::shared_ptr<Spaceship> player_;

    raylib::Vector2 generateRandomPos();

    void launchProjectile();

public:
    GameManager();

    std::shared_ptr<Asteroid> createAsteroid(raylib::Vector2 position, Asteroid::Size size, float rotation);

    void spawnAsteroid();

    void splitAsteroid(Asteroid::Size);

    void spawnSpaceship();

    void update();

    void drawObjects() const;

    void drawHud() ;

    bool intersects(shared_ptr<GameObject>, shared_ptr<GameObject>) const;

    void checkCollision();

    bool gameStatus() const;

    void reset();
};