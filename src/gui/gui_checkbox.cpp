#include "gui_checkbox.hpp"

bool    check_checkbox(gui_base *gui)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        return (checkbox->get_checked());
    return (false);
}

void    set_checkbox(gui_base *gui, bool checked)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        checkbox->set_checked(checked);
}