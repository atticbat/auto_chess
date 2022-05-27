#include "gui_button.hpp"

void    set_button(gui_base *gui, bool pressed)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        button->set_checked(pressed);
}


game_state  check_button_destination(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->get_destination());
    return (MENU);
}

game_state  check_buttons(std::multimap <gui_type, gui_base *> *gui, \
    game_state current_state)
{
    auto    range = gui->equal_range(G_BUTTON);
    for (auto i = range.first; i != range.second; ++i)
    {
        gui_button  *button = dynamic_cast<gui_button *> (i->second);

        if (button && button->get_checked())
            return (button->get_destination());
    }
    return (current_state);
}