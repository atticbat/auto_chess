#ifndef GUI_HPP
# define GUI_HPP

# include "../raylib-cpp/include/raygui.h"
# include <stdlib.h>
# include <map>
# include "sprite.hpp"
# define RAYGUI_IMPLEMENTATION

class gui_base
{
protected:
    char        *text = NULL;
    Rectangle   bounds;
    int         unique_id = 0;
    int         gui_id = 0;
    int         text_size = 32;
    const char  *text_modes[11] = {"LabelText", "DynamicLabelText", \
        "CheckBoxText", "ButtonText", "SliderText", "ScrollbarText", \
        "DropdownText", "TextboxText", "DragDropText", "ProgressBarLText", \
        "ProgressBarRText"};
    const char  *bound_modes[11] = {"LabelBounds", "DynamicLabelBounds", \
        "CheckBoxBounds", "ButtonBounds", "SliderBounds", "ScrollbarBounds", \
        "DropdownBounds", "TextboxBounds", "DragDropBounds", \
        "ProgressBarBounds", "dummy"};
public:
    ~gui_base()
    {
        if (text)
        {
            free (text);
            text = NULL;
        }
    }
    virtual void    set_bounds(int offset_x, int offset_y, int mode, \
        mINI::INIFile file, float multiplier)
    {
        mINI::INIStructure ini;
        float param[4];
        int i;
        char    str[20];
        int from = 0;
        int to = 0;
        char    c[5];

        ft_itoa(gui_id, c);
        file.read(ini);
        i = 0;
        strlcpy(str, ini.get(bound_modes[mode]).get(c).c_str(), 20);
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
        bounds = (Rectangle) { (param[0] + offset_x) * multiplier, (param[1] \
            + offset_y) * multiplier, param[2] * multiplier, param[3] * \
            multiplier };
    }

    virtual void    set_text(int id, int mode, int size, mINI::INIFile file)
    {
        mINI::INIStructure  ini;
        char                *ptr;
        size_t              len;
        char    c[5];

        gui_id = id;
        text_size = size;
        ft_itoa(id, c);
        file.read(ini);
        len = ini.get(text_modes[mode]).get(c).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
        text = ptr;
    }
    void                set_id(int id) { unique_id = id; }
    Rectangle           get_bounds(void) { return (bounds); }
    virtual char        *get_text(void) { return (text); }
    int                 get_id(void) { return (unique_id); }
    int                 get_gui_id(void) { return (gui_id); }
    int                 get_text_size(void) {return (text_size); }
    void                set_text_size(int new_size) { text_size = new_size; }
};

class gui_dynamic_label : public gui_base
{
private:
    int     value = 0;
    int     original_length = 0;
    bool    percentage = false;
public:
    void    set_text(int id, int mode, int size, mINI::INIFile file)
    {
        mINI::INIStructure  ini;
        char                *ptr;
        size_t              len;
        char    c[5];

        gui_id = id;
        text_size = size;
        ft_itoa(id, c);
        file.read(ini);
        len = ini.get(text_modes[mode]).get(c).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
        text = ptr;
        original_length = strlen(text);
    }
    void    update_text(int _value, bool _percentage)
    {
        char    value_string[5];
        char    text_buffer[10];

        value = _value;
        percentage = _percentage;
        ft_itoa(value, value_string);
        if (percentage)
            strlcat(value_string, "%", 5);
        strlcpy(text_buffer, text, 10);
        if (text)
            free (text);
        text = (char *) malloc (sizeof(char) * (original_length + strlen(value_string) + 2));
        strlcpy(text, text_buffer, original_length + 1);
        strlcat(text, value_string, original_length + strlen(value_string) + 2);
    }
};

class gui_dropdown : public gui_base
{
private:
    bool    edit_mode = false;
    int     default_x = 0;
    int     default_y = 0;
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
protected:
    float   value = 0;
    float   min = 0;
    float   max = 100;
public:
    gui_slider(float _value, float _min, float _max)
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
    int         max_input = 5;
    bool        edit_mode = false;
    int         input_count = 0;
    const int   db_max_input[13] = {3, 1, 2, 2, 2, 4, 5, 4, 4, 4, 1, 4, 4};
public:
    void    set_text(int id, int size)
    {
        gui_id = id;
        text_size = size;
        max_input = db_max_input[id];
        text = (char *) malloc (sizeof(char) * (max_input + 1));
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

class gui_drag_drop : public gui_base
{
private:
    bool        is_picked = false;
    bool        display = false;
    int         unit_id = 0;
    sprite_base *sprite = NULL;
public:
    void        set_is_picked_up (bool _is_picked) { is_picked = _is_picked; }
    bool        get_is_picked_up (void) { return (is_picked); }
    void        generate_picked_up_sprite (int id, int frames)
    {
        sprite = new sprite_picked_up(unit_id, frames, 1);
        unit_id = 0;
    }
    void        generate_static_sprite (int id, int frames)
    {
        sprite = new sprite_base(id, frames, 2);
    }
    void        remove_sprite(void)
    {
        if (sprite)
        {
            delete (sprite);
            sprite = NULL;
        }
    }
    void        draw_sprite(Vector2 point)
    {
        sprite_picked_up    *picked_up = static_cast <sprite_picked_up *> (sprite);

        if (picked_up && point.x != 0 && point.y != 0)
            DrawTextureRec(picked_up->get_image(), picked_up->get_source(), \
                picked_up->get_offset_location(point), WHITE);
        else
            DrawTextureRec(sprite->get_image(), sprite->get_source(), \
                Vector2 {bounds.x + (bounds.width - sprite->get_width()) / 2, bounds.y - sprite->get_image().height * 3/4}, WHITE);
                //change inbound: move bottom of sprite y to middle of gui y
    }
    void        set_unit_id(int id) { unit_id = id; }
    int         get_unit_id(void) { return (unit_id); }
    int         get_sprite_id(void)
    {
        if (sprite)
            return (sprite->get_unit_id());
        return (0);
    }
    void        set_sprite_id(int id) { sprite->set_unit_id(id); }
    void        set_display(bool _display) { display = _display; }
    bool        get_display(void) { return (display); }

};

class gui_progress_bar : public gui_slider
{
private:
    char    *text_right = NULL;
public:
    gui_progress_bar(int _value, int _min, int _max) : gui_slider(_value, \
        _min, _max) { ; }
    ~gui_progress_bar()
    {
        if (text)
            free(text);
        if (text_right)
            free(text_right);
    }
    void    set_text_right(int id, int mode, int size, mINI::INIFile file)
    {
        mINI::INIStructure  ini;
        char                *ptr;
        size_t              len;
        char                c[5];

        gui_id = id;
        text_size = size;
        ft_itoa(id, c);
        file.read(ini);
        len = ini.get(text_modes[mode]).get(c).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
        text_right = ptr;
    }
    char    *get_text_right(void) { return (text_right); }
};

#endif