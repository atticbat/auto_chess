#include "auto_chess.hpp"
// #include <stdio.h>

// static sprite   *initialise_case(game_state current_state, int *unique_id, int offset, int screen_width, int screen_height)
// {
//     sprite  *btn;

//     switch (current_state)
//     {
//         case (MENU)
//         {
//             btn = initialise_menu(unique_id, 64);
//         } break;
//         case (DATABASE)
//         {
//             btn = initialise_db(&unique_id, 64, screen_width, screen_height);
//         } break;
//         default:
//         {
//             btn = NULL;
//             break;
//         }
//     }
//     return (btn);
// }

int main(void)
{
    const int   screen_width = 1600;
    const int   screen_height = 900;
    int         unique_id = 0;
    game_state  current_state = LOADING;
    int         frame_count = 0;
    sprite      *btn_menu;
    input_box   *in_db;
    int         i = 0;
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    InitWindow(screen_width, screen_height, "auto_chess");
    btn_menu = initialise_menu(&unique_id, 64);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();

        switch(current_state)
        {
            case LOADING:
            {
                frame_count++;
                if (frame_count > 90)
                    current_state = MENU;
            } break;
            case MENU:
            {
                current_state = check_menu(btn_menu, mousePoint);
                if (current_state == DATABASE)
                {
                    unload_sprite(&btn_menu, MENU_BUTTONS);
                    btn_menu = initialise_db(&unique_id, 64, screen_width, screen_height);
                    in_db = initialise_db_in(screen_width);
                    
                }
                else if (current_state == SETTINGS)
                    unload_sprite(&btn_menu, MENU_BUTTONS);
                else if (current_state == DRAFT)
                    unload_sprite(&btn_menu, MENU_BUTTONS);
            } break;
            case SETTINGS:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    current_state = MENU;
                    btn_menu = initialise_menu(&unique_id, 64);
                }
            } break;
            case DRAFT:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = SIMULATION;
            } break;
            case SIMULATION:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    current_state = MENU;
                    btn_menu = initialise_menu(&unique_id, 64);
                }
            } break;
            case DATABASE:
            {
                current_state = check_database(btn_menu, in_db, mousePoint, &frame_count);
                if (current_state == MENU)
                {
                    unload_sprite(&btn_menu, DATABASE_BUTTONS);
                    btn_menu = initialise_menu(&unique_id, 64);
                }
            }
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
                    draw_menu(btn_menu, screen_width, screen_height);
                } break;
                case SETTINGS:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, LIGHTGRAY);
                    DrawText("SETTINGS", 120, 160, 20, DARKGRAY);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKGRAY);
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
                case DATABASE:
                {
                    draw_database(btn_menu, in_db, screen_width, screen_height, frame_count);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return (0);
}