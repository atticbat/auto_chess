#include "menu.hpp"

void draw_menu_gui(gui_base **menu_gui)
{
    for (int i = 0; i < 5; i++)
    {
        gui_button  *temp = dynamic_cast<gui_button *> (menu_gui[i]);
        if (temp)
            temp->set_checked(GuiButton(temp->get_bounds(), temp->get_text())); 
    }
}

void set_menu_boundaries(gui_base **menu_gui)
{
    mINI::INIFile   file("data/menu_gui.ini");
    const char      *bound_modes[2] = { "ButtonBounds", "dummy" };

    for (int i = 0; i < 5; i++)
    {
        menu_gui[i]->set_bounds(0, 0, i, bound_modes[0], file);
        printf("Rectangle: x: %f, y: d, width: d, height: d\n", menu_gui[i]->get_bounds().x);
    }
}

game_state   parse_destination(int id)
{
    mINI::INIFile       file ("data/menu_gui.ini");
    mINI::INIStructure  ini;
    char                c[2];

    c[0] = '0' + id;
    c[1] = '\0';
    file.read(ini);
    return (static_cast <game_state>(atoi(ini.get("ButtonDestination").get(c).c_str())));
}

gui_base    **initialise_menu(void)
{
    mINI::INIFile   file("data/menu_gui.ini");
    gui_base        **menu_gui;
    gui_base        **ptr;
    const char      *text_modes[2] = { "ButtonText", "dummy" };

    menu_gui = (gui_base **) malloc (sizeof(gui_base *) * 5);
    ptr = menu_gui;
    for (int i = 0; i < 5; i++)
    {
        gui_button  *button = new gui_button;
        button->set_text(i, (const char *) text_modes[0], file);
        button->set_destination(parse_destination(i));
        *ptr = button;
        if (i < 4)
            ptr++;
    }
    return (menu_gui);
}