#ifndef GUI_DRAG_DROP_HPP
# define GUI_DRAG_DROP_HPP

# include "gui.hpp"

void    check_drag_drops(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point);
// void    drag_drop_controls(std::multimap <gui_type, gui_base *> *gui, \
    gui_base *second, Vector2 mouse_point);
void    del_sprites(std::multimap <gui_type, gui_base *> *gui);
void    draw_drag_drops(gui_base *gui, Vector2 mouse_point);

#endif