#ifndef GUI_HPP
# define GUI_HPP

# include "../raylib-cpp/include/ini.h"
# include "../raylib-cpp/include/raygui.h"
# include <stdlib.h>
# include "game_progression.hpp"
# include "input_box.hpp"
# define RAYGUI_IMPLEMENTATION

void        ft_itoa(int num, char *buffer);

class gui_base
{
protected:
    char                *text = NULL;
    Rectangle           bounds;
public:
    virtual void        set_bounds(int offset_x, int offset_y, int id, const char *mode, mINI::INIFile file)
    {
        mINI::INIStructure ini;
        float param[4];
        int i;
        char    str[16];
        int from = 0;
        int to = 0;
        char    c[5];

        ft_itoa(id, c);
        file.read(ini);
        i = 0;
        strlcpy(str, ini.get(mode).get(c).c_str(), 16);
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

    virtual void        set_text(int id, const char *mode, mINI::INIFile file)
    {
        mINI::INIStructure  ini;
        char                *ptr;
        size_t              len;
        char    c[2];
   
        c[0] = id + '0';
        c[1] = '\0';
        file.read(ini);
        len = ini.get(mode).get(c).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get(mode).get(c).c_str(), len + 1);
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
};

class gui_dropdown : public gui_base
{
private:
    bool    edit_mode = false;
    int     default_x;
    int     default_y;
public:
    int     choice = 3;
    int     get_default_x(void) { return (default_x); }
    int     get_default_y(void) { return (default_y); }
    void    set_default(int width, int height)
    {
        default_x = width;
        default_y = height;
    }
    bool    get_edit_mode(void) { return (edit_mode); }
    void    toggle_edit_mode(void) { edit_mode = !edit_mode; }
};

class gui_slider : public gui_base
{
private:
    char    *text_right = NULL;
    float   value = 0;
    float   min = 0;
    float   max = 100;
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

class gui_textbox : public gui_base
{
private:
    int     max_input;
    bool    edit_mode = false;
    int     input_count = 0;
public:
    void    set_max_input(int max)
    {
        max_input = max;
        text = (char *) malloc (sizeof(char) * (max + 1));
    }
    void    set_edit_mode(bool mode) { edit_mode = mode; }
    bool    get_edit_mode(void) { return(edit_mode); }
    bool    check_if_max(void)
    {
        if (input_count == max_input)
            return (true);
        return (false);
    }
    void    add_letter(char letter)
    {
        if (!check_if_max())
        {
            text[input_count] = letter;
            input_count++;
            text[input_count] = '\0';
        }
    }
    void    delete_letter(void)
    {
        if (input_count > 0)
        {
            input_count--;
            text[input_count] = '\0';
        }
    }
};

class gui_scrollbar : public gui_base
{
private:
    Rectangle   content;
public:
    Vector2     scroll = { 99, -20 };
    void        set_bounds(float x, float y, float width, float height)
    {
        bounds = (Rectangle) { x, y, width, height };
    }
    void        set_content(float x, float y, float width, float height)
    {
        content = (Rectangle) { x, y, width, height };
    }
    Rectangle   get_content(void) { return (content); }
};

bool        check_checkbox(gui_base *gui);
bool        check_button_press(gui_base *gui);
game_state  check_button_destination(gui_base *gui);
int         check_default_x(gui_base *gui);
int         check_default_y(gui_base *gui);

#endif