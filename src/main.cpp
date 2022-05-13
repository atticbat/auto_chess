#include "auto_chess.hpp"

int main(void)
{
    const int   screen_width = 800;
    const int   screen_height = 450;
    game_state  current_state;
    int         frame_count;

    InitWindow(screen_width, screen_height, "auto_chess");
    current_state = LOADING;
    frame_count = 0;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        switch(current_state)
        {
            case LOADING:
            {
                frame_count++;
                if (frame_count > 120)
                    current_state = MENU;
            } break;
            case MENU:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = DRAFT;
            } break;
            case DRAFT:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = SIMULATION;
            } break;
            case SIMULATION:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = MENU;
            } break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (current_state)
            {
                case LOADING:
                {
                    DrawText("LOADING...", 20, 20, 40, LIGHTGRAY);
                    DrawText("PLEASE WAIT.", 290, 220, 20, GRAY);
                } break;
                case MENU:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, BLUE);
                    DrawText("MENU", 120, 160, 20, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to JUMP to DRAFT SCREEN", 120, 220, 20, DARKBLUE);
                } break;
                case DRAFT:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, YELLOW);
                    DrawText("DRAFT", 120, 160, 20, DARKBROWN);
                    DrawText("PRESS ENTER or TAP to JUMP to SIMULATION SCREEN", 120, 220, 20, DARKBROWN);
                } break;
                case SIMULATION:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, PINK);
                    DrawText("SIMULATION", 120, 160, 20, DARKPURPLE);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKPURPLE);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return (0);
}