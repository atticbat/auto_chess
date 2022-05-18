#include "auto_chess.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../raylib-cpp/include/raygui.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const int   screen_width = 1920;
    const int   screen_height = 1080;
    const int   header_offset = 64 * (((DATABASE_INPUTS) * 160) / (screen_width - 160)) + 96;
    int         unique_id = 0;
    game_state  current_state = LOADING;
    int         frame_count = 0;
    sprite      *btn_menu;
    input_box   *in_db;
    int         i = 0;
    char        name_buffer[50];
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    InitWindow(screen_width, screen_height, "auto_chess");

    Rectangle panelRec = { 0, header_offset, screen_width, screen_height - header_offset };
    Rectangle panelContentRec = { 0, header_offset, 1080, 2880 };
    Vector2 panelScroll = { 99, -20 };

    gui_dropdown    drop_downs[2];
    int     resolution_chosen[2] = { 0, 0 };
    bool    resolution_edit_mode[2] = { false, false };

    btn_menu = initialise_menu(&unique_id, 64);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();

        frame_count++;
        switch(current_state)
        {
            case LOADING:
            {
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
                {
                    unload_sprite(&btn_menu, MENU_BUTTONS);
                    btn_menu = initialise_settings(&unique_id, 32, screen_width, screen_height);
                    drop_downs[0].set_dropdown_bounds((screen_width - 960)/2, (screen_height - 540)/2, 0);
                    drop_downs[0].set_name(0);
                    // drop_downs[1].set_dropdown_bounds((screen_width - 960)/2, (screen_height - 540)/2, 1);
                    // drop_downs[1].set_name(0);
                }
                else if (current_state == DRAFT)
                    unload_sprite(&btn_menu, MENU_BUTTONS);
            } break;
            case SETTINGS:
            {
                current_state = check_settings(btn_menu, mousePoint);
                if (CheckCollisionPointRec(mousePoint, drop_downs[0].bounds) && IsGestureDetected(GESTURE_TAP))
                    resolution_edit_mode[0] = !resolution_edit_mode[0];
                if (current_state == MENU)
                {
                    unload_sprite(&btn_menu, SETTINGS_BUTTONS);
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
                    ClearBackground(RAYWHITE);
                    draw_menu(btn_menu, screen_width, screen_height);
                } break;
                case SETTINGS:
                {
                    draw_settings(btn_menu, screen_width, screen_height);
                    GuiDropdownBox(drop_downs[0].bounds, drop_downs[0].names, &resolution_chosen[0], resolution_edit_mode[0]);
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
                    GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll);
                    draw_grid(panelScroll.x, panelScroll.y);
                    draw_database(btn_menu, in_db, screen_width, screen_height, frame_count);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return (0);
}
