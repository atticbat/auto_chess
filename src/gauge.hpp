#ifndef GAUGE_HPP
# define GAUGE_HPP

# include "gui/gui_base.hpp"

class   gauge
{
private:
    Color       colour = (Color) { 0, 0, 0, 255 };
    float       current_value = 0;
    float       max_value = 100;
    int         unit_width = 128;
    int         gauge_height = 16;
    Rectangle   bounds = (Rectangle) {0, 0, 0, 0} ;
public:
    gauge(Color _colour, float current, float max, int width)
    {
        colour = _colour;
        current_value = current;
        max_value = max;
        unit_width = width;
    }
    Rectangle   get_bounds(void) { return (bounds); }
    Color       get_colour(void) { return (colour); }
    void        set_value(float value) { current_value = value; }
    void        set_bounds(float x, float y)
    {
        bounds = (Rectangle) {x, y, (current_value / max_value) * unit_width, \
            (float) gauge_height};
    }
};

#endif