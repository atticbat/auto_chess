#include "gui_button.hpp"

bool	gui_button::get_checked(void)
{
    if (checked)
    {
        checked = false;
        return (true);
    }
    return (checked);
}

void    set_button(gui_base *gui, bool pressed)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        button->checked = pressed;
}

gui_button  *generate_button(int i, mINI::INIFile file)
{
    gui_button  *button = new gui_button;

    button->set_text(i, 3, 24, file);
    button->destination = parse_destination(i, file);
    button->unique_id = i;
    return (button);
}

game_state  check_button_destination(gui_base *gui)
{
    gui_button *button = dynamic_cast<gui_button *> (gui);

    if (button)
        return (button->destination);
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
            return (button->destination);
    }
    return (current_state);
}

void    change_button_destination(int new_destination, int id, \
    mINI::INIFile file)
{
    mINI::INIStructure ini;
    char    buffer[5];
    char    buffer2[5];

    ft_itoa(new_destination, buffer);
    ft_itoa(id, buffer2);
    file.read(ini);
    ini["ButtonDestination"][buffer2] = buffer;
    file.write(ini);
}