#include "auto_chess.hpp"
#include <stdlib.h>
#include <stdio.h>

void    draw (std::multimap <gui_type, gui_base *> *gui, game_settings \
    settings, std::map <int, sprite_multi *> *sprites, \
    std::multimap <particle_type, particle *> *particles, char **unit_db)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (settings.state)
        {
            case LOADING:
            {
                DrawText("LOADING...", 20, 20, 40, LIGHTGRAY);
            } break;
            case APPLY:
            case SETTINGS:
            {
                DrawRectangle((settings.screen_dim.x - settings.settings_dim.x \
                    ) / 2, (settings.screen_dim.y - settings.settings_dim.y) \
                    / 2, settings.settings_dim.x, settings.settings_dim.y, \
                    GRAY);
            } break;
            case REROLL:
            case DRAFT:
            {
                DrawRectangle(0, settings.screen_dim.y * 0.75, \
                    settings.screen_dim.x, settings.screen_dim.y * 0.25, \
                    BROWN);
            } break;
            case SIMULATION:
            {
                draw_simulation(particles, sprites, settings);
                if (!(settings.user->get_ongoing_game()))
                    DrawRectangle(0, 0, settings.screen_dim.x, \
                        settings.screen_dim.y, Color { 0, 0, 0, 125 });
            } break;
            case EDIT_UNIT:
            case DATABASE:
            {
                DrawRectangle(0, 0, settings.screen_dim.x, 64 * (((\
                DATABASE_INPUTS) * 160) / (settings.screen_dim.x - 160)) \
                    + 96, LIME);

            } break;
            default: break;
        }
        draw_gui(gui, settings);
        if (settings.state == DATABASE)
            draw_grid(check_scrollbar_x(find_gui_by_id(gui, 15, G_SCROLLBAR)), \
                check_scrollbar_y(find_gui_by_id(gui, 15, G_SCROLLBAR)), \
                unit_db);
    EndDrawing(); 
}

int main(void)
{
    game_settings   settings;
    initialise_game(&settings);
    char            **unit_db = NULL;
    std::multimap <gui_type, gui_base *> gui;
    std::multimap <particle_type, particle *> particles;
    std::map <int, sprite_multi *> sprites;

    while (!settings.exit_window)
    {
        if (WindowShouldClose())
            settings.exit_window = true;
        settings.mouse_point = GetMousePosition();
        settings.frame_count++;
        switch(check_gui(&gui, &settings))
        {
            case LOADING:
            {
                settings.state = loading_controls(&gui, settings);
            } break;
            case MENU:
            {
                unit_db = menu_controls(&gui, &settings, unit_db);
            } break;
            case SETTINGS:
            {
                unit_db = settings_controls(&gui, &sprites, &settings, \
                    unit_db);
            } break;
            case LOAD:
            {
                enter_load(&gui, &(settings.user), settings.scale);
                settings.state = DRAFT;
            } break ;
            case DRAFT:
            {
                unit_db = draft_controls(&gui, &sprites, &settings, unit_db);
            } break;
            case SIMULATION:
            {
                unit_db = simulation_controls(&gui, &sprites, &settings, \
                    &particles, unit_db);
            } break;
            case DATABASE:
            {
                unit_db = database_controls(&gui, &settings, unit_db);
            } break;
            case APPLY:
            {
                apply_settings(&gui, &settings);
                update_sprite_size(&settings, settings.user->get_sprite_size());
                settings.state = SETTINGS;
            } break ;
            case EDIT_UNIT:
            {
                edit_unit(&gui, unit_db);
                del_db(unit_db);
                unit_db = initialise_unit_db();
                settings.state = DATABASE;
            } break ;
            case REROLL:
            {
                reroll_shop(&gui, settings.user);
                update_dlabels(&gui, settings.user);
                settings.state = DRAFT;
            } break ;
            case BUY_XP:
            {
                buy_xp(&gui, settings.user);
                settings.state = DRAFT;
            } break ;
            case EXIT:
            {
                settings.exit_window = true;
            } break ;
            default: break;
        }
        draw (&gui, settings, &sprites, &particles, unit_db);
    }
    CloseWindow();
    system("leaks auto_chess");
    return (0);
}
