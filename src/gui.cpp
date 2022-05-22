#include "gui.hpp"

bool    check_checkbox(gui_base *gui)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        return (checkbox->get_checked());
    return (false);
}

bool    check_button_press(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->get_checked());
    return (false);
}

game_state  check_button_destination(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->get_destination());
    return (MENU);
}

int check_default_x(gui_base *gui)
{
    gui_dropdown *dropdown = dynamic_cast<gui_dropdown *> (gui);

    if (dropdown)
        return (dropdown->get_default_x());
    return (1920);
}

int check_default_y(gui_base *gui)
{
    gui_dropdown *dropdown = dynamic_cast<gui_dropdown *> (gui);

    if (dropdown)
        return (dropdown->get_default_y());
    return (1080);
}