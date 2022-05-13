#include "auto_chess.hpp"

int main (void)
{
    const int   screen_width = 800;
    const int   screen_height = 450;

    InitWindow(screen_width, screen_height, "raylib[core] example - basic window");
    SetTargetFPS (60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return (0);
}