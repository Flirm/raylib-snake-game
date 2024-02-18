#include "include/raylib.h"
#include "headers/ball.h"
#include <random>
#include <iostream>
#include <ctime>

Ball::Ball()
{
    //generating seed from time
    srand(static_cast<unsigned int>(std::time(nullptr)));
    this->rect.height = 16;
    this->rect.width = 16;
    this->rect.x = 0;
    this->rect.y = 0;
}

//spawn ball in a random positon in the grid in screen
void Ball::spawn(Player player)
{
    //get random place for ball to spawn
    this->rect.x = 16 * (rand() % ((int)((GetScreenWidth()) / 16)));
    this->rect.y = 16 * (rand() % ((int)((GetScreenHeight()) / 16)));

    //check if ball spawned inside player
    for(int i = 0; i < player.points + 1; i++)
    {
        if(player.position[i].x == this->rect.x && player.position[i].y == this->rect.y)
        {
            spawn(player);
            break;
        }
    }
}

