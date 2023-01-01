#include "gui_checkbox.hpp"

gui_checkbox::gui_checkbox()
{
	checked = false;
}

bool    check_checkbox(gui_base *gui)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        return (checkbox->checked);
    return (false);
}

void    set_checkbox(gui_base *gui, bool checked)
{
    gui_checkbox *checkbox = dynamic_cast<gui_checkbox *> (gui);

    if (checkbox)
        checkbox->checked = checked;
}