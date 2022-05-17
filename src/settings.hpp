#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "sprite.hpp"
# include "../raylib-cpp/include/raygui.h"

# define SETTINGS_BUTTONS 2

sprite      *initialise_settings(int *unique_id, int offset, int screen_width, int screen_height);
void        draw_settings(sprite *btn, int screen_width, int screen_height);
game_state  check_settings(sprite *btn, Vector2 mousePoint);

#endif