#include "gui_dynamic_label.hpp"

void    update_label(gui_base *gui, default_run *user)
{
    gui_dynamic_label   *label = dynamic_cast <gui_dynamic_label *> (gui);

    if (label)
        label->update_text(user->get_gold(), false);
}