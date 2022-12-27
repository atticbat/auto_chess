#include "menu.hpp"
#include "gui/gui_button.hpp"

void    initialise_menu(std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile   file("data/menu_gui.ini");

    for (int i = 0; i < 5; i++)
    {
        gui_button  *button = new gui_button;
        button->set_text(i, 3, 24, file);
        button->destination = parse_destination(i, file);
        gui->insert(std::pair<gui_type, gui_button *> (G_BUTTON, button));
    }
}
