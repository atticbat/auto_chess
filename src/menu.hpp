#ifndef MENU_HPP
# define MENU_HPP

# define MENU_BUTTONS 5
# include "sprite.hpp"

sprite          *initialise_menu(int *unique_id, int offset);
void            draw_menu(sprite *btn, int screen_width, int screen_height);
game_state      check_menu(sprite *btn, Vector2 mousePoint);
void            unload_menu(sprite *btn);

#endif