#include "settings.hpp"

int parse_resolution(int id)
{
    mINI::INIFile       file ("data/settings_gui.ini");
    mINI::INIStructure  ini;
    char                c[5];

    ft_itoa(id, c);
    file.read(ini);
    return (stoi(ini.get("ResolutionX").get(c)));
}

static int  parse_choice(int id)
{
    mINI::INIFile       file ("data/settings_gui.ini");
    mINI::INIStructure  ini;
    char                c[5];

    ft_itoa(id, c);
    file.read(ini);
    return (stoi(ini.get("DropdownDefaultChoice").get(c)));
}

Vector2     get_screen_dim(void)
{
    return ((Vector2) { (float) parse_resolution(parse_choice(0)), \
        (float) (parse_resolution(parse_choice(0)) / 16) * 9 });
}

void    initialise_settings(std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile   file ("data/settings_gui.ini");

    for (int i = 0; i < 5; i++)
    {
        gui_base    *label = new gui_base;

        label->set_text(i, 0, 32, file);
        label->set_id(i);
        gui->insert(std::pair<gui_type, gui_base *> (G_LABEL, label));
    }
    for (int i = 5; i < 7; i++)
    {
        gui_checkbox    *checkbox = new gui_checkbox;

        if (IsWindowFullscreen() && i - 5 == 0)
            checkbox->set_checked(true);
        checkbox->set_id(i);
        gui->insert(std::pair<gui_type, gui_base *> (G_CHECKBOX, checkbox));
    }
    for (int i = 7; i < 9; i++)
    {
        gui_button  *button = new gui_button;

        button->set_text(i - 7, 3, 24, file);
        button->set_destination(parse_destination(i - 7, file));
        button->set_id(i);
        gui->insert(std::pair<gui_type, gui_base *> (G_BUTTON, button));
    }
    {
        gui_slider  *slider =  new gui_slider(50, 0, 100);

        slider->set_id(9);
        gui->insert(std::pair<gui_type, gui_base *> (G_SLIDER, slider));
    }
    for (int i = 10; i < 12; i++)
    {
        gui_dropdown    *dropdown =  new gui_dropdown;

        dropdown->set_text(i - 10, 6, 24, file);
        dropdown->choice = parse_choice(i - 10); 
        if (i == 10)
            dropdown->set_default(parse_resolution(dropdown->choice), \
                (parse_resolution(dropdown->choice) / 16) * 9);
        dropdown->set_id(i);
        gui->insert(std::pair<gui_type, gui_base *> (G_DROPDOWN, dropdown));
    }
}

void    apply_settings(std::multimap <gui_type, gui_base *> *gui, Vector2 \
    *screen_dim, Vector2 max_dim, Vector2 settings_dim)
{
    mINI::INIFile file ("data/settings_gui.ini");

    if (check_checkbox(find_gui_by_id(gui, 5, G_CHECKBOX)) && \
        !IsWindowFullscreen())
    {
        screen_dim->x = max_dim.x;
        screen_dim->y = max_dim.y;
        SetWindowSize(screen_dim->x, screen_dim->y);
        ToggleFullscreen();
        set_boundaries(gui, (screen_dim->x - settings_dim.x) / 2, \
            (screen_dim->y - settings_dim.y) / 2, file, 1);
    }
    else if (!check_checkbox(find_gui_by_id(gui, 5, G_CHECKBOX)) && \
        IsWindowFullscreen())
    {
        ToggleFullscreen();
        screen_dim->x = check_default_x(find_gui_by_id(gui, 10, G_DROPDOWN));
        screen_dim->y = check_default_y(find_gui_by_id(gui, 10, G_DROPDOWN));
        SetWindowSize(screen_dim->x, screen_dim->y);
        set_boundaries(gui, (screen_dim->x - settings_dim.x) / 2, \
            (screen_dim->y - settings_dim.y) / 2, file, 1);
    }
    else if (!IsWindowFullscreen())
    {
        screen_dim->x = check_default_x(find_gui_by_id(gui, 10, G_DROPDOWN));
        screen_dim->y = check_default_y(find_gui_by_id(gui, 10, G_DROPDOWN));
        SetWindowSize(screen_dim->x, screen_dim->y);
        set_boundaries(gui, (screen_dim->x - settings_dim.x) / 2, \
            (screen_dim->y - settings_dim.y) / 2, file, 1);
    }
    mINI::INIStructure ini;
    char    holder[5];
    ft_itoa(check_dropdown_choice(find_gui_by_id(gui, 10, G_DROPDOWN)), \
        holder);
    file.read(ini);
    ini["DropdownDefaultChoice"]["0"] = holder;
    file.write(ini);
}