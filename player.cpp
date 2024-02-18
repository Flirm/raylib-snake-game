#include "include/raylib.h"
#include "headers/player.h"
#include <random>
#include <iostream>

static Vector2 lastSnakePos[SNAKE_LEN];

Player::Player()
{
    this->size.y = 16;
    this->size.x = 16;
    this->position[0].x = 16 * (rand() % ((int)((GetScreenWidth()) / 16)));
    this->position[0].y = 16 * (rand() % ((int)((GetScreenHeight()) / 16)));
    this->direction.x = 0;
    this->direction.y = 0;
    this->speed = 16;
    this->move_delay = 0;
    this->points = 0;
    this->dead = false;
    this->canMove = true;
}

void Player::move()
{
    int len = this->points + 1;

    for(int i = 0; i < len; i++)
    {
        lastSnakePos[i].x = this->position[i].x;
        lastSnakePos[i].y = this->position[i].y;
    }

    Vector2 newDir;



    newDir.x = IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT);
    newDir.y = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);
        
    if((newDir.x != 0 || newDir.y != 0) && !(newDir.x && newDir.y) && ((newDir.x != -1*this->direction.x) || (newDir.y != -1*this->direction.y)) && this->canMove)
    {
        this->direction.x = newDir.x;
        this->direction.y = newDir.y;
        this->canMove = false;
    }

    if(this->move_delay >= 0.125)
    {
        this->move_delay = 0;

        this->position[0].x += this->direction.x * this->speed;
        this->position[0].y += this->direction.y * this->speed;
        
        this->canMove = true;

        for(int i = 1; i < len; i++)
        {   
            this->position[i].x = lastSnakePos[i-1].x;
            this->position[i].y = lastSnakePos[i-1].y;

            if(this->position[0].x == this->position[i].x && this->position[0].y == this->position[i].y)
            {
                this->dead = true;
            }
        }
    }
    else
    {
        this->move_delay += GetFrameTime();
    }

}


void Player::draw()
{
    int len = this->points + 1;

    for(int i = 0; i < len; i++)
    {
        DrawRectangleV(this->position[i], this->size, BLACK);
    }

}
