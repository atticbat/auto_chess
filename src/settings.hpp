#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "sprite.hpp"
# include "../raylib-cpp/include/raygui.h"
# include "../raylib-cpp/include/ini.h"
# include <stdlib.h>
# include <stdio.h>
# define RAYGUI_IMPLEMENTATION

# define SETTINGS_BUTTONS 2

class gui_base
{
protected:
    char                *text = NULL;
    char    *text_right = NULL;
    float   value = 0;
    float   min = 0;
    float   max = 100;
private:
    const char          *i_to_c[6] = {"0", "1", "2", "3", "4", "5"};
    const char          *bound_modes[5] = {"LabelBounds", "SliderBounds", "DropdownBounds", "CheckBoxBounds", "ButtonBounds"};
    const char          *text_modes[3] = {"LabelText", "DropdownText", "ButtonText"};
    Rectangle           bounds;
public:
    //can't have virtual variables so this choice variable has to be here now for dropdown
    int                 choice = 0;
    //
    void                set_bounds(int offset_x, int offset_y, int id, int mode)
    {
        mINI::INIFile file ("data/settings_gui.ini");
        mINI::INIStructure ini;
        float param[4];
        int i;
        char    str[16];
        int from = 0;
        int to = 0;

        file.read(ini);
        i = 0;
        strlcpy(str, ini.get(bound_modes[mode]).get(i_to_c[id]).c_str(), 16);
        while (i < 4)
        {
            param[i] = 0;
            to = from;
            while (str[to] != ',' && str[to] != '\0')
                to++;
            while (from < to)
            {
                param[i] = (param[i] * 10) + (str[from] - '0');
                from++;
            }
            i++;
            if (i < 4)
                from = to + 1;
        }
        bounds = (Rectangle) { param[0] + offset_x, param[1] + offset_y, param[2], param[3] };
    }
    virtual void        set_text(int id, int mode)
    {
        mINI::INIFile       file ("data/settings_gui.ini");
        mINI::INIStructure  ini;
        char                *ptr;
        size_t              len;

        file.read(ini);
        len = ini.get(text_modes[mode]).get(i_to_c[id]).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get(text_modes[mode]).get(i_to_c[id]).c_str(), len + 1);
        text = ptr;
    }
    void                free_text(void) 
    {
        if (text)
        {
            free(text);
            text = NULL;
        }
    }
    Rectangle           get_bounds(void) { return (bounds); }
    virtual char        *get_text(void) { return (text); }
    //virtual functions needed for dynamic polymorphism
    // virtual void        value_init(int, int, int) { ; }
    // virtual bool        get_checked(void) { return (false); }
    // virtual game_state  get_destination(void) { return (MENU); }
    // virtual void        toggle_edit_mode(void) { ; }
    // virtual float       get_value(void) { return (0); }
    // virtual float       get_min(void) { return (0); }
    // virtual float       get_max(void) { return (0); }
    // virtual bool        get_edit_mode(void) { return (false); }
    // virtual void        set_checked(bool) { ; }
    // virtual void        set_value(int) { ; }
    //
};

class gui_dropdown : public gui_base
{
private:
    bool    edit_mode = false;
public:
    // int     choice = 0;
    // bool    edit_mode = false;
    bool    get_edit_mode(void) { return (edit_mode); }
    void    toggle_edit_mode(void) { edit_mode = !edit_mode; }
};

class gui_slider : public gui_base
{
// private:
//     char    *text_right = NULL;
//     float   value = 0;
//     float   min = 0;
//     float   max = 100;
public:
    char        *get_text(int side) 
    { 
        if (side == 1)
            return (text_right);
        return (text);
    }
    void        value_init(float _value, float _min, float _max)
    {
        value = _value;
        min = _min;
        max = _max;
    }
    void        set_value(float _value) { value = _value; }
    float       get_value(void) { return (value); }
    float       get_min(void) { return (min); }
    float       get_max(void) { return (max); }
};

class gui_checkbox : public gui_base
{
protected:
    bool    checked = false;
public:
    // void    toggle_checked(void) { checked = !checked; }
    virtual void    set_checked(bool _checked) { checked = _checked; }
    bool            get_checked(void) { return (checked); }
};

class gui_button : public gui_checkbox
{
private:
    game_state  destination = MENU;
public:
    game_state  get_destination(void) { return (destination); }
    void        set_destination(game_state to) { destination = to; }
    bool        get_checked(void)
    {
        if (checked)
        {
            checked = false;
            return (true);
        }
        return (checked);
    }
};

game_state  check_settings(sprite *btn, Vector2 mousePoint);
sprite  *initialise_settings(int *unique_id, int offset, int screen_width, int screen_height);
void    draw_settings(sprite *btn, int screen_width, int screen_height);

#endif