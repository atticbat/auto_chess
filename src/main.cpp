#include "auto_chess.hpp"
#include <stdlib.h>
#include <stdio.h>

static void enter_menu(std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile file("data/menu_gui.ini");
    mINI::INIFile file2("data/settings_gui.ini");

    initialise_menu(gui);
    set_boundaries(gui, 0, 0, file, 1);
    change_button_destination(1, 0, file2);
}

static void enter_settings(std::multimap <gui_type, gui_base *> *gui, \
    game_settings settings)
{
    mINI::INIFile file("data/settings_gui.ini");

    initialise_settings(gui);
    set_boundaries(gui, (settings.screen_dim.x - settings.settings_dim.x) \
        / 2, (settings.screen_dim.y - settings.settings_dim.y) / 2, file, 1);
}

static char **enter_database(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 screen_dim)
{
    mINI::INIFile file("data/database_gui.ini");

    initialise_database(gui);
    set_database_boundaries(gui, screen_dim); 
    return (initialise_unit_db());
}

static void enter_new_game(std::multimap <gui_type, gui_base *> *gui, \
    default_run **user, float scale)
{
    mINI::INIFile file("data/draft_gui.ini");
    mINI::INIFile file2("data/settings_gui.ini");

    delete (*user);
    *user = new default_run();
    write_changes(*user);
    initialise_draft(gui, *user);
    reroll_shop(gui, *user);
    set_boundaries(gui, 0, 0, file, scale);
    change_button_destination(7, 0, file2);
}

static void enter_load(std::multimap <gui_type, gui_base *> *gui, \
    default_run **user, float scale)
{
    mINI::INIFile file("data/draft_gui.ini");
    mINI::INIFile file2("data/settings_gui.ini");

    load_user(*user);
    initialise_draft(gui, *user);
    set_boundaries(gui, 0, 0, file, scale);
    change_button_destination(7, 0, file2);
}

static void enter_simulation(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, game_settings settings, \
    default_run *user)
{
    char    **unit_db;
    mINI::INIFile file("data/simulation_gui.ini");
    mINI::INIFile file2("data/settings_gui.ini");

    unit_db = initialise_unit_db();
    if (!(user->get_ongoing_game()))
    {
        initialise_simulation(sprites, user, settings.sprite_size, unit_db);
        user->toggle_ongoing_game();
    }
    initialise_sim_gui(gui);
    set_boundaries(gui, 0, 0, file, settings.scale);
    for (int i = 0; i < 128; i++)
        free (unit_db[i]);
    free (unit_db);
    change_button_destination(4, 0, file2);
}

static void initialise_game(game_settings *settings)
{
    InitWindow(0, 0, "Auto Chess");
    settings->max_dim = { (float) GetScreenWidth(), (float) \
        GetScreenHeight() };
    settings->screen_dim = get_screen_dim();
    settings->scale = settings->screen_dim.x / settings->max_dim.x;
    SetWindowSize(settings->screen_dim.x, settings->screen_dim.y);
    SetTargetFPS(60);

    settings->mouse_point = { 0.0f, 0.0f };
    settings->settings_dim = { 800, 450 };
    settings->exit_window = false;
    settings->frame_count = 0;
    settings->sprite_size = get_sprite_size();
    settings->x_offset = -(56 * (256 * settings->sprite_size) - \
        settings->screen_dim.x) / 2;
    settings->state = LOADING;
}

int main(void)
{
    game_settings   settings;
    initialise_game(&settings);
    char            **unit_db = NULL;
    default_run     *user = new default_run();
    std::multimap <gui_type, gui_base *> gui;
    std::multimap <particle_type, particle *> particles;
    std::map <int, sprite_multi *> sprites;

    while (!settings.exit_window)
    {
        if (WindowShouldClose())
            settings.exit_window = true;
        settings.mouse_point = GetMousePosition();
        settings.frame_count++;
        switch(settings.state)
        {
            case LOADING:
            {
                if (settings.frame_count > 60)
                {
                    settings.state = MENU;
                    enter_menu(&gui);
                }
            } break;
            case MENU:
            {
                settings.state = check_gui(&gui, settings, user);
                if (settings.state != MENU)
                    del_gui(&gui);
                if (settings.state == SETTINGS)
                    enter_settings(&gui, settings);
                else if (settings.state == DATABASE)
                    unit_db = enter_database(&gui, settings.screen_dim);
                else if (settings.state == DRAFT)
                    enter_new_game(&gui, &user, settings.scale);
            } break;
            case SETTINGS:
            {
                settings.state = check_gui(&gui, settings, user);
                settings.scale = settings.screen_dim.x / settings.max_dim.x;
                if (settings.state != SETTINGS && (int)settings.state < 8)
                    del_gui(&gui);
                if (settings.state == MENU)
                    enter_menu(&gui);
                if (settings.state == DRAFT)
                    enter_load(&gui, &user, settings.scale);
                if (settings.state == SIMULATION)
                    enter_simulation(&gui, &sprites, settings, user);
            } break;
            case LOAD:
            {
                enter_load(&gui, &user, settings.scale);
                settings.state = DRAFT;
            } break ;
            case DRAFT:
            {
                write_changes(user);
                settings.state = check_gui(&gui, settings, user);
                if (settings.state != DRAFT && (int)settings.state < 8)
                {
                    del_sprites(&gui);
                    del_gui(&gui);
                }
                if (settings.state == MENU)
                    enter_menu(&gui);
                if (settings.state == SETTINGS)
                    enter_settings(&gui, settings);
                if (settings.state == SIMULATION)
                    enter_simulation(&gui, &sprites, settings, user);
            } break;
            case SIMULATION:
            {
                settings.state = check_gui(&gui, settings, user);
                simulation(&particles, &sprites, &settings, user, &gui);
                if (settings.state != SIMULATION && (int)settings.state < 8)
                    del_gui(&gui);
                if (settings.state == DRAFT)
                    enter_load(&gui, &user, settings.scale);
                if (settings.state == SETTINGS)
                    enter_settings(&gui, settings);
            } break;
            case DATABASE:
            {
                settings.state = check_gui(&gui, settings, user);
                if (settings.state != DATABASE && (int)settings.state < 8)
                {
                    del_db(unit_db);
                    unit_db = NULL;
                    del_gui(&gui);
                }
                if (settings.state == MENU)
                    enter_menu(&gui);
            } break;
            case APPLY:
            {
                apply_settings(&gui, &settings, user);
                switch (user->get_sprite_size())
                {
                    case 0:
                    {
                        settings.sprite_size = 1;
                    } break ;
                    case 1:
                    {
                        settings.sprite_size = 0.75;
                    } break ;
                    case 2:
                    {
                        settings.sprite_size = 0.5;
                    } break;
                    case 3:
                    {
                        settings.sprite_size = 0.25;
                    } break ;
                    default: break ;
                }
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
                if (user->get_gold() > 0)
                {
                    reroll_shop(&gui, user);
                    user->deduct_gold(1);
                }
                settings.state = DRAFT;
            } break ;
            case BUY_XP:
            {
                if (user->get_gold() > 0)
                {
                    user->deduct_gold(1);
                    user->add_exp(2);
                    gui_progress_bar *bar = dynamic_cast <gui_progress_bar *> \
                    (find_gui_by_id(&gui, 36, G_PROGRESS_BAR));

                    if (bar)
                    {
                        bar->set_value(user->get_exp());
                        bar->set_max(user->get_exp_cap());
                    }
                    gui_dynamic_label   *label = dynamic_cast <gui_dynamic_label *> \
                        (find_gui_by_id(&gui, 1, G_DYNAMIC_LABEL));
                    
                    if (label)
                        label->update_text(user->get_level(), false);
                }
                settings.state = DRAFT;
            } break ;
            case EXIT:
            {
                settings.exit_window = true;
            } break ;
            default: break;
        }
        BeginDrawing();
            switch (settings.state)
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
                    draw_gui(&gui, settings);
                } break;
                case APPLY:
                case SETTINGS:
                {
                    ClearBackground(DARKBROWN);
                    DrawRectangle((settings.screen_dim.x - \
                        settings.settings_dim.x)/2, (settings.screen_dim.y \
                        - settings.settings_dim.y)/2, settings.settings_dim.x,\
                        settings.settings_dim.y, RAYWHITE);
                    draw_gui(&gui, settings);
                } break;
                case REROLL:
                case DRAFT:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, settings.screen_dim.y * 0.75, \
                        settings.screen_dim.x, settings.screen_dim.y * 0.25, \
                        BROWN);
                    draw_gui(&gui, settings);
                } break;
                case SIMULATION:
                {
                    ClearBackground(RAYWHITE);
                    draw_simulation(&particles, &sprites, settings);
                    if (!(user->get_ongoing_game()))
                        DrawRectangle(0, 0, settings.screen_dim.x, \
                            settings.screen_dim.y, Color { 0, 0, 0, 125 });
                    draw_gui(&gui, settings);
                } break;
                case EDIT_UNIT:
                case DATABASE:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, settings.screen_dim.x, 64 * (((\
                    DATABASE_INPUTS) * 160) / (settings.screen_dim.x - 160)) \
                        + 96, LIME);
                    draw_gui(&gui, settings);
                    draw_grid(check_scrollbar_x(find_gui_by_id(&gui, 15, \
                        G_SCROLLBAR)), check_scrollbar_y(find_gui_by_id(&gui, \
                        15, G_SCROLLBAR)), unit_db);
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    system("leaks auto_chess");
    return (0);
}
