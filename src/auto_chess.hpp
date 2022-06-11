#ifndef AUTO_CHESS_HPP
# define AUTO_CHESS_HPP

// # include <string>
// # include <iostream>
// # include <fstream>
// # include <sstream>
// # include <random>
// # include <tgmath.h>
// # include <map>
// # include "../include/json_struct.h"
// # include "../raylib-cpp/include/raylib-cpp.hpp"
// # include "../raylib-cpp/include/raygui.h"
// # include "../config.hpp"
// # include "sprite.hpp"
// # include "input_box.hpp"
# include "menu.hpp"
# include "database.hpp"
# include "settings.hpp"
// # include "gui.hpp"
// # include "storyboard_controls.hpp"
// # include "game_progression.hpp"
# include "draft.hpp"
// # include "gui_checkbox.hpp"
// # include "gui_button.hpp"
// # include "gui_slider.hpp"
// # include "gui_scrollbar.hpp"
// # include "gui_dropdown.hpp"
// # include "unit_stats.hpp"
// # include "battle_sim.hpp"
# include "simulation.hpp"

void    initialise_game(game_settings *settings);
void    enter_simulation(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, game_settings *settings);
void    enter_load(std::multimap <gui_type, gui_base *> *gui, \
    default_run **user, float scale);
void    enter_new_game(std::multimap <gui_type, gui_base *> *gui, \
    default_run **user, float scale);
char    **enter_database(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 screen_dim);
void    enter_settings(std::multimap <gui_type, gui_base *> *gui, \
    game_settings settings);
void    enter_menu(std::multimap <gui_type, gui_base *> *gui);
char    **database_controls(std::multimap <gui_type, gui_base *> *gui, \
    game_settings *settings, char **unit_db);
char    **simulation_controls(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, game_settings *settings, \
    std::multimap <particle_type, particle *> *particles, char **unit_db);
char    **menu_controls(std::multimap <gui_type, gui_base *> *gui, \
    game_settings *settings, char **unit_db);
game_state  loading_controls(std::multimap <gui_type, gui_base *> *gui, \
    game_settings settings);
char    **settings_controls(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, game_settings *settings, \
    char **unit_db);
char    **draft_controls(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, game_settings *settings, \
    char **unit_db);

#endif