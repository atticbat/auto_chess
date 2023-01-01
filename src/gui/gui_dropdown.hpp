#ifndef GUI_DROPDOWN_HPP
# define GUI_DROPDOWN_HPP

# include "gui_base.hpp"

class gui_dropdown : public gui_base
{
public:
    bool    edit_mode;
    bool    is_resolution;
    int     default_x;
    int     default_y;
    int     choice;
	gui_dropdown();
    void    set_default(int width, int height);
    void    toggle_edit_mode(void);
};

int         check_dropdown_choice(gui_base *gui);
int         *get_dropdown_choice_ptr(gui_base *gui);
int         check_default_x(gui_base *gui);
int         check_default_y(gui_base *gui);
bool        check_dropdown_edit_mode(gui_base *gui);
void        set_dropdown_default(gui_base *gui, int x, int y);
void        check_dropdowns(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point);
void        draw_dropdowns(gui_base *gui);

#endif