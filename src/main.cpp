#include "auto_chess.hpp"
#include <stdlib.h>
#include <stdio.h>

// void    overwrite_user(default_run *user)
// {
//     mINI::INIFile   file ("data/user_settings.ini");
//     mINI::INIStructure ini;
//     char    holder[5];
//     file.read(ini);
//     for (int i = 0; i < 8; i++)
//     {
//         ft_itoa(i, holder);
//         ini["Roster"][holder] = "0";
//     }
//     ini["UserSettings"]["name"] = user->get_name();
//     ft_itoa(user->get_gold(), holder);
//     ini["UserSettings"]["gold"] = holder;
//     ft_itoa(user->get_level(), holder);
//     ini["UserSettings"]["level"] = holder;
//     ini["UserSettings"]["exp"] = "0";
//     ini["UserSettings"]["wins"] = "0";
//     ini["UserSettings"]["losses"] = "0";
//     file.write(ini);
// }

static void change_settings_return(int new_destination)
{
    mINI::INIFile file ("data/settings_gui.ini");
    mINI::INIStructure ini;
    char    buffer[5];

    ft_itoa(new_destination, buffer);
    file.read(ini);
    ini["ButtonDestination"]["0"] = buffer;
    file.write(ini);
}

static void enter_menu(std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile file("data/menu_gui.ini");

    initialise_menu(gui);
    set_boundaries(gui, 0, 0, file, 1);
    change_settings_return(1);
}

static void enter_settings(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 screen_dim, Vector2 settings_dim)
{
    mINI::INIFile file("data/settings_gui.ini");

    initialise_settings(gui);
    set_boundaries(gui, (screen_dim.x - settings_dim.x) / 2, \
        (screen_dim.y - settings_dim.y) / 2, file, 1);
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

    delete (*user);
    *user = new default_run();
    write_changes(*user);
    initialise_draft(gui, *user);
    reroll_shop(gui, *user);
    set_boundaries(gui, 0, 0, file, scale);
    change_settings_return(7);
}

static void enter_load(std::multimap <gui_type, gui_base *> *gui, \
    default_run **user, float scale)
{
    mINI::INIFile file("data/draft_gui.ini");

    load_user(*user);
    initialise_draft(gui, *user);
    set_boundaries(gui, 0, 0, file, scale);
    change_settings_return(7);
}

static char **enter_simulation(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, default_run *user)
{
    char    **unit_db;
    // mINI::INIFile file("data/simulation_gui.ini");

    unit_db = initialise_unit_db();
    initialise_simulation(gui, sprites, user, unit_db);
    return (unit_db);
}

int main(void)
{
    InitWindow(0, 0, "Auto Chess");
    const Vector2   max_dim = { (float) GetScreenWidth(), (float) \
        GetScreenHeight() };
    Vector2         screen_dim = get_screen_dim();
    float           scale = screen_dim.x / max_dim.x;
    SetWindowSize(screen_dim.x, screen_dim.y);
    SetTargetFPS(60);

    Vector2         mouse_point = { 0.0f, 0.0f };
    const Vector2   settings_dim = { 800, 450 };
    char            **unit_db = NULL;
    bool            exit_window = false;
    int             frame_count = 0;
    default_run     *user = new default_run();
    std::multimap <gui_type, gui_base *> gui;
    std::multimap <particle_type, particle *> particles;
    std::map <int, sprite_multi *> sprites;
    int             x_offset = -2000;
    game_state      state = LOADING;
    while (!exit_window)
    {
        if (WindowShouldClose())
            exit_window = true;
        mouse_point = GetMousePosition();
        frame_count++;
        switch(state)
        {
            case LOADING:
            {
                if (frame_count > 60)
                {
                    state = MENU;
                    enter_menu(&gui);
                }
            } break;
            case MENU:
            {
                state = check_gui(&gui, mouse_point, state, user);
                if (state != MENU)
                    del_gui(&gui);
                if (state == SETTINGS)
                    enter_settings(&gui, screen_dim, settings_dim);
                else if (state == DATABASE)
                    unit_db = enter_database(&gui, screen_dim);
                else if (state == DRAFT)
                    enter_new_game(&gui, &user, scale);
            } break;
            case SETTINGS:
            {
                state = check_gui(&gui, mouse_point, state, user);
                scale = screen_dim.x / max_dim.x;
                if (state != SETTINGS && (int)state < 8)
                    del_gui(&gui);
                if (state == MENU)
                    enter_menu(&gui);
                if (state == DRAFT)
                    enter_load(&gui, &user, scale);
            } break;
            case LOAD:
            {
                enter_load(&gui, &user, scale);
                state = DRAFT;
            } break ;
            case DRAFT:
            {
                write_changes(user);
                state = check_gui(&gui, mouse_point, state, user);
                if (state != DRAFT && (int)state < 8)
                {
                    del_sprites(&gui);
                    del_gui(&gui);
                }
                if (state == MENU)
                    enter_menu(&gui);
                if (state == SETTINGS)
                    enter_settings(&gui, screen_dim, settings_dim);
                if (state == SIMULATION)
                    unit_db = enter_simulation(&gui, &sprites, user);
            } break;
            case SIMULATION:
            {
                simulation(&particles, &sprites, &x_offset, frame_count);
            } break;
            case DATABASE:
            {
                state = check_gui(&gui, mouse_point, state, user);
                if (state != DATABASE && (int)state < 8)
                {
                    del_db(unit_db);
                    unit_db = NULL;
                    del_gui(&gui);
                }
                if (state == MENU)
                    enter_menu(&gui);
            } break;
            case APPLY:
            {
                apply_settings(&gui, &screen_dim, max_dim, settings_dim);
                state = SETTINGS;
            } break ;
            case EDIT_UNIT:
            {
                edit_unit(&gui, unit_db);
                del_db(unit_db);
                unit_db = initialise_unit_db();
                state = DATABASE;
            } break ;
            case REROLL:
            {
                if (user->get_gold() > 0)
                {
                    reroll_shop(&gui, user);
                    user->deduct_gold(1);
                }
                state = DRAFT;
            } break ;
            case EXIT:
            {
                exit_window = true;
            }
            default: break;
        }
        BeginDrawing();
            switch (state)
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
                case REROLL:
                case DRAFT:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, screen_dim.y * 0.75, screen_dim.x, \
                        screen_dim.y * 0.25, BROWN);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                } break;
                case SIMULATION:
                {
                    ClearBackground(RAYWHITE);
                    draw_simulation(&particles, &sprites, x_offset);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
                } break;
                case EDIT_UNIT:
                case DATABASE:
                {
                    ClearBackground(RAYWHITE);
                    DrawRectangle(0, 0, screen_dim.x, 64 * (((\
                    DATABASE_INPUTS) * 160) / (screen_dim.x - 160)) \
                        + 96, LIME);
                    draw_gui(&gui, screen_dim, settings_dim, mouse_point);
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
