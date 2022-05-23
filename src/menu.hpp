#ifndef MENU_HPP
# define MENU_HPP

# define MENU_BUTTONS 5
# include "sprite.hpp"
# include "gui.hpp"

// sprite          *initialise_menu(int *unique_id, int offset);
// void            draw_menu(sprite *btn, int screen_width, int screen_height);
// game_state      check_menu(sprite *btn, Vector2 mousePoint);
// void            unload_menu(sprite *btn);
gui_base    **initialise_menu(void);
game_state  parse_destination(int id);
void        set_menu_boundaries(gui_base **menu_gui);
void        draw_menu_gui(gui_base **menu_gui);
game_state  check_menu(gui_base **menu_gui);
void        del_menu(gui_base **menu_gui);

#endif