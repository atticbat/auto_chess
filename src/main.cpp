#include "auto_chess.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../raylib-cpp/include/raygui.h"
#include <stdlib.h>
#include <stdio.h>

gui_base    **initialise_draft (void)
{
    gui_base        **draft_gui;
    gui_base        **ptr;
    mINI::INIFile   file ("data/draft_gui.ini");
    const char      *text_modes[3] = {"LabelText", "DragDropText"};

    draft_gui = (gui_base **) malloc (sizeof(gui_base *) * 6);
    ptr = draft_gui;
    for (int i = 0; i < 5; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;
        drag_drop->set_text(i, text_modes[1], file);
        *ptr = drag_drop;
        ptr++;
    }
    return (draft_gui);
}

void    set_draft_boundaries(gui_base **draft_gui, Vector2 screen_dim)
{
    mINI::INIFile   file("data/draft_gui.ini");
    const char      *bound_modes[5] = {"LabelBounds", "DragDropBounds"};

    for (int i = 0; i < 5; i++)
        draft_gui[i]->set_bounds(screen_dim.x * 0.35 + i * (screen_dim.y * 0.2125), screen_dim.y * 0.775, i, bound_modes[1], file);
}

void    draw_draft_gui(gui_base **draft_gui, Vector2 screen_dim)
{
    ClearBackground(RAYWHITE);
    DrawRectangle(0, screen_dim.y * 0.75, screen_dim.x, screen_dim.y * 0.25, BROWN);
    for (int i = 0; i < 5; i++)
    {
        gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> (draft_gui[i]);

        if (drag_drop && drag_drop->get_is_picked_up())
            GuiDrawRectangle(drag_drop->get_mouse_bounds(), 1, BLACK, RAYWHITE);
        else if (drag_drop)
            GuiDrawRectangle(drag_drop->get_bounds(), 1, BLACK, RAYWHITE);
    }
}

int main(void)
{
    InitWindow(0, 0, "Auto Chess");
    game_state      current_state = LOADING;
    int             frame_count = 0;
    Vector2         screen_dim = get_screen_dim();
    const Vector2   max_dim = { (float) GetScreenWidth(), (float) GetScreenHeight() };
    const Vector2   settings_dim = { 800, 450 };
    Vector2         mouse_point = { 0.0f, 0.0f };
    bool            exit_window = false;
    gui_base        **gui = initialise_menu();

    SetWindowSize(screen_dim.x, screen_dim.y);
    set_menu_boundaries(gui);

    //draft stuff
    gui_base    **draft_gui = initialise_draft();
    set_draft_boundaries(draft_gui, screen_dim);
    //draft stuff

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
                current_state = check_menu(gui);
                if (current_state != MENU)
                    del_menu(gui);
                if (current_state == SETTINGS)
                {
                    gui = initialise_settings();
                    set_settings_boundaries(gui, screen_dim, settings_dim);
                }
                else if (current_state == DATABASE)
                {
                    gui = initialise_database(); 
                    set_database_boundaries(gui, screen_dim);
                }
            } break;
            case SETTINGS:
            {
                current_state = check_settings(gui, &screen_dim, max_dim, settings_dim, mouse_point);
                if (current_state != SETTINGS)
                    del_settings(gui);
                if (current_state == MENU)
                {
                    gui = initialise_menu();
                    set_menu_boundaries(gui);
                }
            } break;
            case DRAFT:
            {
                for (int i = 0; i < 5; i++)
                {
                    gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> (draft_gui[i]);
                    if (drag_drop && drag_drop->get_is_picked_up())
                        drag_drop->set_mouse_bounds(mouse_point);
                    if (drag_drop && CheckCollisionPointRec(mouse_point, drag_drop->get_mouse_bounds()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        drag_drop->set_is_picked_up(true);
                    if (drag_drop && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        drag_drop->set_is_picked_up(false);
                        drag_drop->set_mouse_bounds((Vector2) {drag_drop->get_bounds().x, drag_drop->get_bounds().y} );
                    }
                }
            } break;
            case SIMULATION:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    current_state = MENU;
                    gui = initialise_menu();
                    set_menu_boundaries(gui);
                }
            } break;
            case DATABASE:
            {
                current_state = check_database(gui, mouse_point, &frame_count);
                if (current_state != DATABASE)
                    del_database(gui);
                if (current_state == MENU)
                {
                    gui = initialise_menu();
                    set_menu_boundaries(gui);                   
                }
            } break;
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
                    draw_menu_gui(gui);
                } break;
                case SETTINGS:
                {
                    draw_settings_gui(gui, screen_dim, settings_dim);
                } break;
                case DRAFT:
                {
                    for (int i = 0; i < 8; i++)
                        DrawRectangle(i * (screen_dim.x / 8) + screen_dim.x / 48, screen_dim.y / 2, screen_dim.x / 12, screen_dim.y / 16, DARKGREEN);
                    draw_draft_gui(draft_gui, screen_dim);
                } break;
                case SIMULATION:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_dim.x, screen_dim.y, PINK);
                    DrawText("SIMULATION", 120, 160, 20, DARKPURPLE);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKPURPLE);
                } break;
                case DATABASE:
                {
                    draw_database(gui, screen_dim);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    system("leaks auto_chess");
    return (0);
}
