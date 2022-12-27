#ifndef GUI_SLIDER_HPP
# define GUI_SLIDER_HPP

# include "gui_base.hpp"

class gui_slider : public gui_base
{
public:
    float   value = 0;
    float   min = 0;
    float   max = 100;
    gui_slider(float _value, float _min, float _max);
};

void        set_slider(gui_base *gui, float value);
float       check_slider_value(gui_base *gui);
float       check_slider_min(gui_base *gui);
float       check_slider_max(gui_base *gui);

#endif