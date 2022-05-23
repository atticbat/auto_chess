#ifndef DATABASE_HPP
# define DATABASE_HPP

# include "../raylib-cpp/include/ini.h"
# include "gui.hpp"

# define DATABASE_BUTTONS 2
# define DATABASE_INPUTS 13
# define MAX_UNITS 128

gui_base    **initialise_database(void);
game_state  check_database(gui_base **db_gui, Vector2 mousePoint, int *frame_count);
void        draw_database(gui_base **db_gui, Vector2 screen_dim);
void        draw_grid(int screen_h_offset, int screen_v_offset);
void        set_database_boundaries(gui_base **settings_gui, Vector2 screen_dim);
void        del_database(gui_base **database_gui);

#endif