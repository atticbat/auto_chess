#ifndef GUI_SCROLLBAR_HPP
# define GUI_SCROLLBAR_HPP

# include "gui_base.hpp"

class gui_scrollbar : public gui_base
{
public:
	gui_scrollbar();
    Rectangle   content;
    Vector2     scroll;
};

void        set_scrollbar_content(gui_base *gui, float x_off, float y_off, \
    float width, float height);
void        set_scrollbar_bounds(gui_base *gui, float off_x, float off_y, \
    float width, float height);
Rectangle   check_scrollbar_content(gui_base *gui);
float       check_scrollbar_x(gui_base *gui);
float       check_scrollbar_y(gui_base *gui);
Vector2     *get_scrollbar_scroll(gui_base *gui);

#endif