#include "auto_chess.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../raylib-cpp/include/raygui.h"
#include <stdlib.h>
#include <stdio.h>

static gui_base **initialise_settings(void)
{
    gui_base        **settings_gui;
    gui_base        **ptr;

    settings_gui = (gui_base **) malloc (sizeof(gui_base *) * 12);
    ptr = settings_gui;
    for (int i = 0; i < 5; i++)
    {
        gui_base    *label = new gui_base;
        label->set_text(i, 0);
        *ptr = label;
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        *ptr = new gui_checkbox;
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        gui_button  *button = new gui_button;
        button->set_text(i, 2);
        *ptr = button;
        ptr++;
    }
    {
        *ptr = new gui_slider;
        gui_slider  *temp = dynamic_cast<gui_slider *> (*ptr);
        temp->value_init(50, 0, 100);
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        gui_dropdown    *dropdown =  new gui_dropdown;
        dropdown->set_text(i, 1);
        *ptr = dropdown;
        if (i == 0)
            ptr++;
    }
    return (settings_gui);
}

static bool check_checkbox(gui_base *gui)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        return (checkbox->get_checked());
    return (false);
}

static bool check_button_press(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->get_checked());
    return (false);
}

static game_state   check_button_destination(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->get_destination());
    return (MENU);
}

static void set_gui_boundaries(gui_base **settings_gui, int screen_width, int screen_height, int settings_width, int settings_height)
{
    for (int i = 0; i < 5; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, 0);
    for (int i = 5; i < 7; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 5, 3);
    for (int i = 7; i < 9; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 7, 4);
    settings_gui[9]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, 0, 1);
    for (int i = 10; i < 12; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 10, 2);
}

static void draw_gui(gui_base **settings_gui)
{
    for (int i = 0; i < 5; i++)
        DrawText(settings_gui[i]->get_text(), settings_gui[i]->get_bounds().x, settings_gui[i]->get_bounds().y, 32, DARKGRAY);
    for (int i = 5; i < 7; i++)
    {
        gui_checkbox    *temp = dynamic_cast<gui_checkbox *> (settings_gui[i]);
        if (temp)
            temp->set_checked(GuiCheckBox(temp->get_bounds(), temp->get_text(), temp->get_checked()));
    }
    for (int i = 7; i < 9; i++)
    {
        gui_button  *temp = dynamic_cast<gui_button *> (settings_gui[i]);
        if (temp)
            temp->set_checked(GuiButton(temp->get_bounds(), temp->get_text())); 
    }
    {
        gui_slider  *temp = dynamic_cast<gui_slider *> (settings_gui[9]);
        if (temp)
            temp->set_value(GuiSliderBar(temp->get_bounds(), NULL, NULL, temp->get_value(), temp->get_min(), temp->get_max()));
    }
    for (int i = 10; i < 12; i++)
    {
        gui_dropdown    *temp = dynamic_cast<gui_dropdown *> (settings_gui[i]);
        if (temp)
            GuiDropdownBox(temp->get_bounds(), temp->get_text(), &(temp->choice), temp->get_edit_mode());
    }
}

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

    gui_base        **settings_gui = initialise_settings();

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
                    set_gui_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                    unload_sprite(&btn_menu, MENU_BUTTONS);
                }
                else if (current_state == DRAFT)
                    unload_sprite(&btn_menu, MENU_BUTTONS);
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
                        set_gui_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
                    }
                    else if (!check_checkbox(settings_gui[5]) && IsWindowFullscreen())
                    {
                        ToggleFullscreen();
                        screen_width = default_width;
                        screen_height = default_height;
                        SetWindowSize(screen_width, screen_height);
                        set_gui_boundaries(settings_gui, screen_width, screen_height, settings_width, settings_height);
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
                if (current_state == MENU)
                    btn_menu = initialise_menu(&unique_id, 64);
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
                    ClearBackground(DARKBROWN);
                    DrawRectangle((screen_width - settings_width)/2, (screen_height - settings_height)/2, settings_width, settings_height, RAYWHITE);
                    draw_gui(settings_gui);
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
    for (int i = 0; i < 12; i++)
        settings_gui[i]->free_text();
    CloseWindow();
    return (0);
}
