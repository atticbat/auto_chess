#ifndef GUI_BUTTON_HPP
# define GUI_BUTTON_HPP

# include "gui.hpp"

// bool        check_button_press(gui_base *gui);
game_state  check_button_destination(gui_base *gui);
void        set_button(gui_base *gui, bool pressed);
game_state  check_buttons(std::multimap <gui_type, gui_base *> *gui, \
    game_state current_state);
gui_button  *generate_button(int i, mINI::INIFile file);
void        change_button_destination(int new_destination, int id, \
    mINI::INIFile file);

#endif