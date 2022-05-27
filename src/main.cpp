#include "auto_chess.hpp"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    InitWindow(0, 0, "Auto Chess");
    game_state      current_state = LOADING;
    int             frame_count = 0;
    Vector2         screen_dim = get_screen_dim();
    const Vector2   max_dim = { (float) GetScreenWidth(), (float) GetScreenHeight() };
    float           res_multiplier = screen_dim.x / max_dim.x;
    const Vector2   settings_dim = { 800, 450 };
    Vector2         mouse_point = { 0.0f, 0.0f };
    bool            exit_window = false;
    std::multimap <gui_type, gui_base *> gui;
    mINI::INIFile file ("data/menu_gui.ini");

    initialise_menu(&gui);
    set_boundaries(&gui, 0, 0, file, 1);
    SetWindowSize(screen_dim.x, screen_dim.y);
    SetTargetFPS(60);
    while (!exit_window)
    {
        if (WindowShouldClose())
            exit_window = true;
        mouse_point = GetMousePosition();
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
                current_state = check_gui(&gui, mouse_point, current_state);
                if (current_state != MENU)
                    del_gui(&gui);
                if (current_state == SETTINGS)
                {
                    initialise_settings(&gui);
                    file.reset("data/settings_gui.ini");
                    set_boundaries(&gui, (screen_dim.x - settings_dim.x) / 2, \
                        (screen_dim.y - settings_dim.y) / 2, file, 1);
                }
                else if (current_state == DATABASE)
                {
                    initialise_database(&gui);
                    initialise_unit_db();
                    file.reset("data/database_gui.ini");
                    set_database_boundaries(&gui, screen_dim);
                }
                else if (current_state == DRAFT)
                {
                    initialise_draft(&gui);
                    file.reset("data/draft_gui.ini");
                    set_boundaries(&gui, 0, 0, file, res_multiplier);
                }
            } break;
            case SETTINGS:
            {
                current_state = check_gui(&gui, mouse_point, current_state);
                res_multiplier = screen_dim.x / max_dim.x;
                if (current_state != SETTINGS && (int)current_state < 8)
                    del_gui(&gui);
                if (current_state == MENU)
                {
                    file.reset("data/menu_gui.ini");
                    initialise_menu(&gui);
                    set_boundaries(&gui, 0, 0, file, 1);
                }
                if (current_state == DRAFT)
                {
                    file.reset("data/draft_gui.ini");
                    initialise_draft(&gui);
                    set_boundaries(&gui, 0, 0, file, 1);
                }
            } break;
            case DRAFT:
            {
                current_state = check_gui(&gui, mouse_point, current_state);
                if (current_state != DRAFT)
                    del_gui(&gui);
                if (current_state == MENU)
                {
                    file.reset("data/menu_gui.ini");
                    initialise_menu(&gui);
                    set_boundaries(&gui, 0, 0, file, 1);
                }
                if (current_state == SETTINGS)
                {
                    initialise_settings(&gui);
                    file.reset("data/settings_gui.ini");
                    set_boundaries(&gui, (screen_dim.x - settings_dim.x) / 2, \
                        (screen_dim.y - settings_dim.y) / 2, file, 1);
                }
            } break;
            case SIMULATION:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    file.reset("data/menu_gui.ini");
                    current_state = MENU;
                    initialise_menu(&gui);
                    set_boundaries(&gui, 0, 0, file, 1);
                }
            } break;
            case DATABASE:
            {
                current_state = check_gui(&gui, mouse_point, current_state);
                if (current_state != DATABASE && (int)current_state < 8)
                    del_gui(&gui);
                if (current_state == MENU)
                {
                    file.reset("data/menu_gui.ini");
                    initialise_menu(&gui);
                    set_boundaries(&gui, 0, 0, file, 1);
                }
            } break;
            case APPLY:
            {
                apply_settings(&gui, &screen_dim, max_dim, settings_dim);
                current_state = SETTINGS;
            } break ;
            case EDIT_UNIT:
            {
                edit_unit(&gui);
                current_state = DATABASE;
            } break ;
            case EXIT:
            {
                exit_window = true;
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
                    ClearBackground(BLUE);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                } break;
                case APPLY:
                case SETTINGS:
                {
                    ClearBackground(DARKBROWN);
                    DrawRectangle((screen_dim.x - settings_dim.x)/2, \
                        (screen_dim.y - settings_dim.y)/2, settings_dim.x, \
                        settings_dim.y, RAYWHITE);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                } break;
                case DRAFT:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, screen_dim.y * 0.75, screen_dim.x, screen_dim.y * 0.25, BROWN);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                } break;
                case SIMULATION:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_dim.x, screen_dim.y, PINK);
                    DrawText("SIMULATION", 120, 160, 20, DARKPURPLE);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKPURPLE);
                } break;
                case EDIT_UNIT:
                case DATABASE:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_dim.x, 64 * (((DATABASE_INPUTS) * 160) / (screen_dim.x - 160)) + 96, LIME);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                    draw_grid(check_scrollbar_x(find_gui_by_id(&gui, 15, \
                        G_SCROLLBAR)), check_scrollbar_y(find_gui_by_id(&gui, \
                        15, G_SCROLLBAR)));
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    system("leaks auto_chess");
    return (0);
}
