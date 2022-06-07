#ifndef GUI_DRAG_DROP_HPP
# define GUI_DRAG_DROP_HPP

# include "gui.hpp"

void            check_drag_drops(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point, default_run *user);
void            del_sprites(std::multimap <gui_type, gui_base *> *gui);
void            draw_drag_drops(gui_base *gui, Vector2 mouse_point);
// gui_drag_drop   *generate_drag_drop(default_run *user, int i, mINI::INIFile \
    file, bool roster_item);

#endif