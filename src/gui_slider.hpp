#ifndef GUI_SLIDER_HPP
# define GUI_SLIDER_HPP

# include "gui.hpp"

void        set_slider(gui_base *gui, float value);
float       check_slider_value(gui_base *gui);
float       check_slider_min(gui_base *gui);
float       check_slider_max(gui_base *gui);

#endif