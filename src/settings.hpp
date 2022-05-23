#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "sprite.hpp"
# include "gui.hpp"
# include "game_progression.hpp"

gui_base    **initialise_settings(void);
void        set_settings_boundaries(gui_base **settings_gui, Vector2 screen_dim, Vector2 settings_dim);
void        draw_settings_gui(gui_base **settings_gui, Vector2 screen_dim, Vector2 settings_dim);
game_state  check_settings(gui_base **settings_gui, Vector2 *screen_dim, Vector2 max_dim, Vector2 settings_dim, Vector2 mouse_point);
void        del_settings(gui_base **settings_gui);
Vector2     get_screen_dim(void);

#endif