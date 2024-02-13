#include <iostream>
#include <memory>
#include <sstream>
#include <variant>

#include "gamemanager.h"
#include "asteroid.h"
#include "spaceship.h"
#include "projectile.h"

GameManager::GameManager()
: score_(0)
{
}

void GameManager::spawnAsteroid()
{
    raylib::Vector2 asteroidPos = generateRandomPos();

    raylib::Vector2 asteroidVelocity {
        static_cast<float>(GetRandomValue(-2, 2)),
        static_cast<float>(GetRandomValue(-2, 2))
    };

    Asteroid::Size asteroidSize = static_cast<Asteroid::Size>(GetRandomValue(0, 2));

    int asteroidRot = GetRandomValue(0, 359);

    objects_.push_back(std::make_shared<Asteroid>(asteroidPos, asteroidRot, asteroidSize, asteroidVelocity));
}

void GameManager::splitAsteroid(Asteroid::Size size)
{
    raylib::Vector2 asteroidPos = generateRandomPos();

    raylib::Vector2 asteroidVelocity {
            static_cast<float>(GetRandomValue(-2, 2)),
            static_cast<float>(GetRandomValue(-2, 2))
    };

    int asteroidRot = GetRandomValue(0, 359);

    objects_.push_back(std::make_shared<Asteroid>(asteroidPos, asteroidRot, size, asteroidVelocity));
}

void GameManager::spawnSpaceship()
{
    raylib::Vector2 shipPos = generateRandomPos();

    auto ship = std::make_shared<Spaceship>(shipPos);
    objects_.push_back(ship);
    player_ = ship;
}

void GameManager::drawObjects() const
{
    for(auto obj : objects_)
    {
        obj->draw();
    }
}

void GameManager::drawHud()
{
    if(player_->getHealth() > 0 && !gameOver_){
        std::stringstream ss;
        ss << "Health: " << player_->getHealth() << std::endl
           << "Score: " << score_ << std::endl;
        DrawText(ss.str().c_str(), 80, 80, 20, LIGHTGRAY);
    }else{
        std::stringstream ss;
        ss << "GAME OVER" << std::endl << "PRESS SPACE TO RESTART" << std::endl << score_ << std::endl;
        DrawRectangle(0,0,1280,1024, BLACK);
        DrawText(ss.str().c_str(), 1280/2 - 100, 1024/2, 20, LIGHTGRAY);
        gameOver_ = true;
    }
}

raylib::Vector2 GameManager::generateRandomPos()
{
    return raylib::Vector2 {
        static_cast<float>(GetRandomValue(0, GetScreenWidth())),
        static_cast<float>(GetRandomValue(0, GetScreenHeight()))
    };
}

void GameManager::update()
{
    GameObjectContainer objectsToDelete;
    // Update objects
    for(auto obj : objects_)
    {
        if(obj->isMarkedForDeletion()) {
            // Überprüfe größe des Asteroid
            std::shared_ptr<Asteroid> asteroid = std::dynamic_pointer_cast<Asteroid>(obj);
            if(asteroid != nullptr && asteroid->getSize() != Asteroid::Size::SMALL)
            {
                if(asteroid->getSize() == Asteroid::Size::MEDIUM){
                    splitAsteroid(Asteroid::Size::SMALL);
                    splitAsteroid(Asteroid::Size::SMALL);
                }else{
                    splitAsteroid(Asteroid::Size::MEDIUM);
                    splitAsteroid(Asteroid::Size::MEDIUM);
                }
            }
            objectsToDelete.push_back(obj);
        }
        else
            obj->update();
    }

    // Delete objects
    for(auto obj : objectsToDelete)
    {
        objects_.remove(obj);
    }

    if(IsKeyPressed(KEY_SPACE))
    {
        launchProjectile();
    }
}

void GameManager::launchProjectile()
{
    auto projectile = std::make_shared<Projectile>(player_->getPosition(), player_->getRotation());
    objects_.push_back(projectile);
}

bool GameManager::intersects(shared_ptr<GameObject> o1,shared_ptr<GameObject> o2) const {
    return CheckCollisionCircles(o1->getPosition(),o1->getWidth()/2,o2->getPosition(),o2->getWidth()/2);
}

void GameManager::checkCollision(){
       for(auto i : objects_){
        for(auto j : objects_) {
            if(i != j){
                if(intersects(i,j)){
                    i->handleCollision(j);
                    j->handleCollision(i);
                }
            }
        }
    }
}

bool GameManager::gameStatus() const{
    return gameOver_;
}

void GameManager::reset(){
    gameOver_ = false;
    player_->setHealth(100);
}

