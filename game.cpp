#include "include/raylib.h"
#include "player.cpp"
#include "ball.cpp"

Player restart(Player player);

int main(void)
{
    //init screen
    const int screenWidth = 400;
    const int screenHeight = 224;
    InitWindow(screenWidth, screenHeight, "SnakeGame");

    //init game objects
    Player player;
    Ball ball;

    //game starting functions
    SetTargetFPS(60);
    ball.spawn(player);

    char pointsText[800];

    //main game loop
    while(!WindowShouldClose())
    {
        //checks if player is outside window
        if(player.position[0].x + 16 > GetScreenWidth() || player.position[0].x < 0 || player.position[0].y + 16 > GetScreenHeight() || player.position[0].y < 0)
        {
            player.dead = true;
            ball.spawn(player);
        }
        //check ball player collision
        if((ball.rect.x == player.position[0].x) && (ball.rect.y == player.position[0].y))
        {
            ball.spawn(player);
            player.points += 1;

        }


        //update point text
        sprintf(pointsText, "%d", player.points);

        player.move();

        //game win end screen
        if(player.points + 1 == 350)
        {
            while(!IsKeyPressed(KEY_ENTER))
            {
                BeginDrawing();

                    ClearBackground(RAYWHITE);
                    DrawText("YOU WIN", GetScreenWidth()/3, GetScreenHeight()/3, 24, BLACK);
                    DrawText("PRESS ENTER TO RESTART", GetScreenWidth()/8, GetScreenHeight()/3 + 32, 24, BLACK);
                
                EndDrawing();

                if(WindowShouldClose()) {CloseWindow(); return 0;}
            }

            player = restart(player);
        }  

        if(player.dead)
        {
            while(!IsKeyPressed(KEY_ENTER))
            {
                BeginDrawing();

                    ClearBackground(RAYWHITE);
                    DrawText("YOU LOST", GetScreenWidth()/3, GetScreenHeight()/3, 24, BLACK);
                    DrawText("PRESS ENTER TO RESTART", GetScreenWidth()/8, GetScreenHeight()/3 + 32, 24, BLACK);
                
                EndDrawing();

                if(WindowShouldClose()) {CloseWindow(); return 0;}
            }
            
            player = restart(player);
        }


        //drawing phase
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(pointsText, GetScreenWidth()/2 - 24, 32, 24, GRAY);

            player.draw();
        
            DrawRectangleRec(ball.rect, RED);

        EndDrawing();

        

    }


    //close opengl content and exit
    CloseWindow();

    return 0;

}

Player restart(Player player)
{
    //destroying previous player instance and recalling the constructor method
    player.~Player();
    new(&player) Player();

    return player;
}