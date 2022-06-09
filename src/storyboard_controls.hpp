#ifndef STORYBOARD_CONTROLS_HPP
# define STORYBOARD_CONTROLS_HPP

# include "gui_checkbox.hpp"
# include "gui_button.hpp"
# include "gui_slider.hpp"
# include "gui_scrollbar.hpp"
# include "gui_dropdown.hpp"
# include "gui_textbox.hpp"
# include "gui_drag_drop.hpp"
# include "gui_dynamic_label.hpp"

int         parse_resolution(int id);
void        input_status_check(gui_textbox *textbox, Vector2 mousePoint);
void        drag_drop_controls(std::multimap <gui_type, gui_base *> *gui, \
    gui_base *second, Vector2 mouse_point);

void        set_boundaries(std::multimap <gui_type, gui_base *> *gui, \
    int off_x, int off_y, mINI::INIFile file, float scale);
void        draw_gui(std::multimap <gui_type, gui_base *> *gui, game_settings \
    settings);
gui_base    *find_gui_by_id(std::multimap <gui_type, gui_base*> *gui, int \
    id, gui_type state);
void        del_gui(std::multimap <gui_type, gui_base *> *gui);
game_state  check_gui(std::multimap <gui_type, gui_base *> *gui, \
    game_settings settings, default_run *user);

#endif