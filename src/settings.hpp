#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "sprite.hpp"
# include "gui.hpp"
# include "game_progression.hpp"

gui_base    **initialise_settings(void);
void        set_settings_boundaries(gui_base **settings_gui, int screen_width, int screen_height, int settings_width, int settings_height);
void        draw_settings_gui(gui_base **settings_gui);

#endif