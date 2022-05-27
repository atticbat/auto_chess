#ifndef GUI_TEXTBOX_HPP
# define GUI_TEXTBOX_HPP

# include "gui.hpp"

void        input_status_check(gui_textbox *textbox, Vector2 mousePoint);
void        check_textboxes(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point);
void        draw_textbox(gui_base *gui);

#endif