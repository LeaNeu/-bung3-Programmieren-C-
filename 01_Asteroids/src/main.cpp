#include "gamemanager.h"

#include <raylib-cpp.hpp>
#include <vector>


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 1024;
    const int numAsteroids = 6;

    raylib::Window window(screenWidth, screenHeight, "B:ME PROG3 Asteroids");
    raylib::Texture background("resources/background.png");

    SetTargetFPS(60);

    GameManager manager;

    for (int i = 0; i < numAsteroids; i++)
    {
        manager.spawnAsteroid();
    }
    manager.spawnSpaceship();

    while (!window.ShouldClose())
    {
        if (manager.gameStatus()) {
            if(IsKeyDown(KEY_SPACE)){
                manager.reset();
            }
        }else{
            BeginDrawing();
            window.ClearBackground(RAYWHITE);
            background.Draw(raylib::Vector2(0, 0));

            manager.update();
            manager.drawObjects();
            manager.drawHud();
            manager.checkCollision();

            EndDrawing();
        }

    }

    return 0;
}