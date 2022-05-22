#include "settings.hpp"
#include <stdio.h>

const int   resolutions[5][2] = { {960, 540}, {1280, 720}, {1600, 900}, {1920, 1080}, {2560, 1440} };

static int  parse_resolution(int id)
{
    mINI::INIFile       file ("data/settings_gui.ini");
    mINI::INIStructure  ini;
    char                c[2];

    c[0] = '0' + id;
    c[1] = '\0';
    file.read(ini);
    return (atoi(ini.get("ResolutionX").get(c).c_str()));
}

static int  parse_choice(int id)
{
    mINI::INIFile       file ("data/settings_gui.ini");
    mINI::INIStructure  ini;
    char                c[2];

    c[0] = '0' + id;
    c[1] = '\0';
    file.read(ini);
    return (atoi(ini.get("DropdownDefaultChoice").get(c).c_str()));
}

gui_base    **initialise_settings(void)
{
    gui_base        **settings_gui;
    gui_base        **ptr;
    mINI::INIFile   file ("data/settings_gui.ini");
    const char      *text_modes[3] = {"LabelText", "DropdownText", "ButtonText"};

    settings_gui = (gui_base **) malloc (sizeof(gui_base *) * 12);
    ptr = settings_gui;
    for (int i = 0; i < 5; i++)
    {
        gui_base    *label = new gui_base;
        label->set_text(i, text_modes[0], file);
        *ptr = label;
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        *ptr = new gui_checkbox;
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        gui_button  *button = new gui_button;
        button->set_text(i, text_modes[2], file);
        *ptr = button;
        ptr++;
    }
    {
        *ptr = new gui_slider;
        gui_slider  *temp = dynamic_cast<gui_slider *> (*ptr);
        temp->value_init(50, 0, 100);
        ptr++;
    }
    for (int i = 0; i < 2; i++)
    {
        gui_dropdown    *dropdown =  new gui_dropdown;
        dropdown->set_text(i, text_modes[1], file);
        dropdown->set_default(parse_resolution(i), (parse_resolution(i) / 16) * 9);
        dropdown->choice = parse_choice(i); 
        *ptr = dropdown;
        if (i == 0)
            ptr++;
    }
    return (settings_gui);
}

void    set_settings_boundaries(gui_base **settings_gui, int screen_width, int screen_height, int settings_width, int settings_height)
{
    mINI::INIFile   file("data/settings_gui.ini");
    const char          *bound_modes[5] = {"LabelBounds", "SliderBounds", "DropdownBounds", "CheckBoxBounds", "ButtonBounds"};

    for (int i = 0; i < 5; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i, bound_modes[0], file);
    for (int i = 5; i < 7; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 5, bound_modes[3], file);
    for (int i = 7; i < 9; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 7, bound_modes[4], file);
    settings_gui[9]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, 0, bound_modes[1], file);
    for (int i = 10; i < 12; i++)
        settings_gui[i]->set_bounds((screen_width - settings_width)/2, (screen_height - settings_height)/2, i - 10, bound_modes[2], file);
}

void    draw_settings_gui(gui_base **settings_gui)
{
    for (int i = 0; i < 5; i++)
        DrawText(settings_gui[i]->get_text(), settings_gui[i]->get_bounds().x, settings_gui[i]->get_bounds().y, 32, DARKGRAY);
    for (int i = 5; i < 7; i++)
    {
        gui_checkbox    *temp = dynamic_cast<gui_checkbox *> (settings_gui[i]);
        if (temp)
            temp->set_checked(GuiCheckBox(temp->get_bounds(), temp->get_text(), temp->get_checked()));
    }
    for (int i = 7; i < 9; i++)
    {
        gui_button  *temp = dynamic_cast<gui_button *> (settings_gui[i]);
        if (temp)
            temp->set_checked(GuiButton(temp->get_bounds(), temp->get_text())); 
    }
    {
        gui_slider  *temp = dynamic_cast<gui_slider *> (settings_gui[9]);
        if (temp)
            temp->set_value(GuiSliderBar(temp->get_bounds(), NULL, NULL, temp->get_value(), temp->get_min(), temp->get_max()));
    }
    for (int i = 10; i < 12; i++)
    {
        gui_dropdown    *temp = dynamic_cast<gui_dropdown *> (settings_gui[i]);
        if (temp)
            GuiDropdownBox(temp->get_bounds(), temp->get_text(), &(temp->choice), temp->get_edit_mode());
        temp->set_default(resolutions[temp->choice][0], resolutions[temp->choice][1]);
    }
}