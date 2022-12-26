#ifndef MENU_HPP
# define MENU_HPP

# define MENU_BUTTONS 5
# include "gui/gui_base.hpp"

void        initialise_menu(std::multimap <gui_type, gui_base *> *gui);

#endif