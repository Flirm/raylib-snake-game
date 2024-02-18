#include "../include/raylib.h"

#define SNAKE_LEN 350

class Player
{
    public:
        Vector2 position[SNAKE_LEN];
        Vector2 size;
        int speed, points;
        float move_delay;
        Vector2 direction;
        bool dead, canMove;
        Player();

        void draw();
        void move();
};
