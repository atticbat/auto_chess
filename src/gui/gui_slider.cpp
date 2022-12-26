#include "gui_slider.hpp"

void    set_slider(gui_base *gui, float value)
{
    gui_slider  *slider = dynamic_cast<gui_slider *> (gui);

    if (slider)
        slider->set_value(value);
}

float   check_slider_value(gui_base *gui)
{
    gui_slider  *slider = dynamic_cast<gui_slider *> (gui);

    if (slider)
        return(slider->get_value()); 
    return (0);
}

float   check_slider_min(gui_base *gui)
{
    gui_slider  *slider = dynamic_cast<gui_slider *> (gui);

    if (slider)
        return(slider->get_min());
    return (0);
}

float   check_slider_max(gui_base *gui)
{
    gui_slider  *slider = dynamic_cast<gui_slider *> (gui);

    if (slider)
        return(slider->get_max()); 
    return (0);
}