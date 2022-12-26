#ifndef GUI_DROPDOWN_HPP
# define GUI_DROPDOWN_HPP

# include "gui_base.hpp"

class gui_dropdown : public gui_base
{
private:
    bool    edit_mode = false;
    bool    is_resolution = false;
    int     default_x = 0;
    int     default_y = 0;
public:
    int     choice = 3;
    int     get_default_x(void) { return (default_x); }
    int     get_default_y(void) { return (default_y); }
    void    set_default(int width, int height)
    {
        default_x = width;
        default_y = height;
    }
    bool    get_edit_mode(void) { return (edit_mode); }
    bool    get_is_resolution(void) { return (is_resolution); }
    void    toggle_edit_mode(void) { edit_mode = !edit_mode; }
    void    set_is_resolution(bool is_res) { is_resolution = is_res; }
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