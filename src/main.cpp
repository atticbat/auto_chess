#include "auto_chess.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../raylib-cpp/include/raygui.h"
#include <stdlib.h>
#include <stdio.h>
// #ifndef PLATFORM_DESKTOP
// # define PLATFORM_DESKTOP 1
// #endif

int main(void)
{
    const int   settings_width = 800;
    const int   settings_height = 450;
    int         unique_id = 0;
    game_state  current_state = LOADING;
    int         frame_count = 0;
    sprite      *btn_menu;
    input_box   *in_db;
    int dim_stop = 0;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(0, 0, "Auto Chess");
    const int   max_width = GetScreenWidth();
    const int   max_height = GetScreenHeight();
    int         screen_width = 1920;
    int         screen_height = 1080;
    const int   default_width = screen_width;
    const int   default_height = screen_height;
    SetWindowSize(screen_width, screen_height);
    const float header_offset = 64 * (((DATABASE_INPUTS) * 160) / (screen_width - 160)) + 96;
    Vector2 mousePoint = { 0.0f, 0.0f };

    Rectangle panelRec = { 0, header_offset, (float) screen_width, screen_height - header_offset };
    Rectangle panelContentRec = { 0, header_offset, 1080, 2880 };
    Vector2 panelScroll = { 99, -20 };

    gui_dropdown    dropdowns[2];
    gui_base        labels[5];
    gui_slider      slider;
    gui_checkbox    checkboxes[2];
    gui_button      buttons[2];
    for (int i = 0; i < 2; i++)
    {
        dropdowns[i].set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, 2);
        dropdowns[i].set_text(i, 1);
    }
    for (int i = 0; i < 5; i++)
    {
        labels[i].set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, 0);
        labels[i].set_text(i, 0);
    }
    slider.set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, 0, 1);
    slider.value_init(50, 0, 100);
    for (int i = 0; i < 2; i++)
        checkboxes[i].set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, 3);
    for (int i = 0; i < 2; i++)
    {
        buttons[i].set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, 4);
        buttons[i].set_text(i, 2);
    }

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
                    dim_stop = frame_count + 16;
                }
                else if (current_state == DRAFT)
                    unload_sprite(&btn_menu, MENU_BUTTONS);
            } break;
            case SETTINGS:
            {
                if (buttons[0].get_checked())
                    current_state = buttons[0].get_destination();
                if (buttons[1].get_checked())
                {
                    if (checkboxes[0].get_checked() && !IsWindowFullscreen())
                    {
                        screen_width = max_width;
                        screen_height = max_height;
                        SetWindowSize(screen_width, screen_height);
                        ToggleFullscreen();
                    }
                    else if (!checkboxes[0].get_checked() && IsWindowFullscreen())
                    {
                        printf("This happens\n");
                        ToggleFullscreen();
                        screen_width = default_width;
                        screen_height = default_height;
                        SetWindowSize(screen_width, screen_height);
                    }
                }
                // if (buttons[1].get_checked() && checkboxes[0].get_checked() && !IsWindowFullscreen())
                // {
                //     screen_width = max_width;
                //     screen_height = max_height;
                //     SetWindowSize(screen_width, screen_height);
                //     ToggleFullscreen();
                // }
                // if (buttons[1].get_checked() && !(checkboxes[0].get_checked()) && IsWindowFullscreen())
                // {
                //     printf("This happens\n");
                //     ToggleFullscreen();
                //     screen_width = default_width;
                //     screen_height = default_height;
                //     SetWindowSize(screen_width, screen_height);
                // }
                for (int i = 0; i < 2; i++)
                {
                    if (CheckCollisionPointRec(mousePoint, dropdowns[i].get_bounds()) && IsGestureDetected(GESTURE_TAP))
                        dropdowns[i].toggle_edit_mode();
                }
                if (current_state == MENU)
                {
                    // for (int i = 0; i < 2; i++)
                    //     dropdowns[i].free_text();
                    // for (int i = 0; i < 5; i++)
                    //     labels[i].free_text();
                    // slider.free_text();
                    // for (int i = 0; i < 2; i++)
                    //     buttons[i].free_text();
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
                    DrawRectangle((screen_width - settings_width)/2, (screen_height - settings_height)/2, settings_width, settings_height, RAYWHITE);
                    if (frame_count < dim_stop)
                        DrawRectangle(0, 0, screen_width, screen_height, (Color) { 0, 0, 0, 30 });
                    for (int i = 0; i < 2; i++)
                        GuiDropdownBox(dropdowns[i].get_bounds(), dropdowns[i].get_text(), &(dropdowns[i].choice), dropdowns[i].edit_mode);
                    for (int i = 0; i < 5; i++)
                        DrawText(labels[i].get_text(), labels[i].get_bounds().x, labels[i].get_bounds().y, 32, DARKGRAY);
                    slider.set_value(GuiSliderBar(slider.get_bounds(), NULL, NULL, slider.get_value(), slider.get_min(), slider.get_max()));
                    for (int i = 0; i < 2; i++)
                        checkboxes[i].set_checked(GuiCheckBox(checkboxes[i].get_bounds(), checkboxes[i].get_text(), checkboxes[i].get_checked()));
                    for (int i = 0; i < 2; i++)
                        buttons[i].set_checked(GuiButton(buttons[i].get_bounds(), buttons[i].get_text()));
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
    for (int i = 0; i < 2; i++)
        dropdowns[i].free_text();
    for (int i = 0; i < 5; i++)
        labels[i].free_text();
    slider.free_text();
    for (int i = 0; i < 2; i++)
        buttons[i].free_text();
    CloseWindow();
    return (0);
}
