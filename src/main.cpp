#include "auto_chess.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../raylib-cpp/include/raygui.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int         unique_id = 0;
    game_state  current_state = LOADING;
    int         frame_count = 0;
    input_box   *in_db;
    
    InitWindow(0, 0, "Auto Chess");
    const int   max_width = GetScreenWidth();
    const int   max_height = GetScreenHeight();
    const int   settings_width = 800;
    const int   settings_height = 450;
    int         screen_width = 1920;
    int         screen_height = 1080;
    SetWindowSize(screen_width, screen_height);
    Vector2 mousePoint = { 0.0f, 0.0f };
    bool        exitWindow = false;

    gui_base        **settings_gui = initialise_settings();
    gui_base        **menu_gui = initialise_menu();
    gui_base        **database_gui = initialise_database();
    set_database_boundaries(database_gui, screen_width, screen_height);

    set_menu_boundaries(menu_gui);
    SetTargetFPS(60);
    while (!exitWindow)
    {
        if (WindowShouldClose())
            exitWindow = true;
        mousePoint = GetMousePosition();
        frame_count++;
        switch(current_state)
        {
            case LOADING:
            {
                if (frame_count > 60)
                    current_state = MENU;
            } break;
            case MENU:
            {
                for (int i = 0; i < 5; i++)
                {
                    if (check_button_press(menu_gui[i]))
                        current_state = check_button_destination(menu_gui[i]);
                }
                if (current_state == SETTINGS)
                {
                    set_settings_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                }
            } break;
            case SETTINGS:
            {
                if (check_button_press(settings_gui[7]))
                    current_state = check_button_destination(settings_gui[7]);
                if (check_button_press(settings_gui[8]))
                {
                    if (check_checkbox(settings_gui[5]) && !IsWindowFullscreen())
                    {
                        screen_width = max_width;
                        screen_height = max_height;
                        SetWindowSize(screen_width, screen_height);
                        ToggleFullscreen();
                        set_settings_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                    }
                    else if (!check_checkbox(settings_gui[5]) && IsWindowFullscreen())
                    {
                        ToggleFullscreen();
                        screen_width = check_default_x(settings_gui[10]);
                        screen_height = check_default_y(settings_gui[10]);
                        SetWindowSize(screen_width, screen_height);
                        set_settings_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                    }
                    else if (!IsWindowFullscreen())
                    {
                        screen_width = check_default_x(settings_gui[10]);
                        screen_height = check_default_y(settings_gui[10]);
                        SetWindowSize(screen_width, screen_height);
                        set_settings_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                    }
                }
                for (int i = 10; i < 12; i++)
                {
                    gui_dropdown    *temp = dynamic_cast<gui_dropdown *> (settings_gui[i]);
                    if (temp)
                    {
                        if (CheckCollisionPointRec(mousePoint, temp->get_bounds()) && IsGestureDetected(GESTURE_TAP))
                            temp->toggle_edit_mode();
                    }
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
                }
            } break;
            case DATABASE:
            {
                current_state = check_database(database_gui, mousePoint, &frame_count);
            } break;
            case EXIT:
            {
                exitWindow = true;
            }
            default: break;
        }
        BeginDrawing();
            switch (current_state)
            {
                case LOADING:
                {
                    ClearBackground(RAYWHITE);
                    DrawText("LOADING...", 20, 20, 40, LIGHTGRAY);
                    DrawText("PLEASE WAIT.", 290, 220, 20, GRAY);
                } break;
                case MENU:
                {
                    ClearBackground(BEIGE);
                    draw_menu_gui(menu_gui);
                } break;
                case SETTINGS:
                {
                    ClearBackground(DARKBROWN);
                    DrawRectangle((screen_width - settings_width)/2, (screen_height - settings_height)/2, settings_width, settings_height, RAYWHITE);
                    draw_settings_gui(settings_gui);
                } break;
                case DRAFT:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_width, screen_height, YELLOW);
                    DrawText("DRAFT", 120, 160, 20, DARKBROWN);
                    DrawText("PRESS ENTER or TAP to JUMP to SIMULATION SCREEN", 120, 220, 20, DARKBROWN);
                } break;
                case SIMULATION:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_width, screen_height, PINK);
                    DrawText("SIMULATION", 120, 160, 20, DARKPURPLE);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKPURPLE);
                } break;
                case DATABASE:
                {
                    ClearBackground(RAYWHITE);
                    draw_database(database_gui, screen_width, screen_height, frame_count);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return (0);
}
