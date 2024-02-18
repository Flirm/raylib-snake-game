#include "../include/raylib.h"

class Ball
{
    public:
        Rectangle rect;
        Ball();

        void spawn(Player player);
};