#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "storyboard_controls.hpp"

void        initialise_settings(std::multimap <gui_type, gui_base *> *gui);
Vector2     get_screen_dim(void);
int         parse_resolution(int id);
void        apply_settings(std::multimap <gui_type, gui_base *> *gui, \
    game_settings *settings);
float       get_sprite_size(void);
void        update_sprite_size(game_settings *settings, int index);

#endif