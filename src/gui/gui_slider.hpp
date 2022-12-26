#ifndef GUI_SLIDER_HPP
# define GUI_SLIDER_HPP

# include "gui_base.hpp"

class gui_slider : public gui_base
{
protected:
    float   value = 0;
    float   min = 0;
    float   max = 100;
public:
    gui_slider(float _value, float _min, float _max)
    {
        value = _value;
        min = _min;
        max = _max;
    }
    void        set_value(float _value) { value = _value; }
    void        set_max(float _value) { max = _value; }
    void        set_min(float _value) { min = _value; }
    float       get_value(void) { return (value); }
    float       get_min(void) { return (min); }
    float       get_max(void) { return (max); }
};



void        set_slider(gui_base *gui, float value);
float       check_slider_value(gui_base *gui);
float       check_slider_min(gui_base *gui);
float       check_slider_max(gui_base *gui);

#endif