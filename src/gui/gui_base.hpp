#ifndef GUI_HPP
# define GUI_HPP

# include <map>
# include "../sprite.hpp"
# include "../../raylib-cpp/include/raygui.h"

typedef enum gui_type {G_LABEL = 0, G_DYNAMIC_LABEL, G_CHECKBOX, G_BUTTON, \
    G_SLIDER, G_SCROLLBAR, G_DROPDOWN, G_TEXTBOX, G_DRAG_DROP, \
    G_PROGRESS_BAR, G_HITBOX} gui_type;

typedef struct  s_game_settings
{
    Vector2     max_dim;
    Vector2     screen_dim;
    float       scale;
    Vector2     mouse_point;
    Vector2     settings_dim;
    bool        exit_window;
    int         frame_count;
    float       sprite_size;
    int         x_offset;
    game_state  state;
    default_run *user;
    bool        initialised = false;
    bool        new_game = false;
}               game_settings;

class gui_base
{
protected:
    const char  *text_modes[11] = {"LabelText", "DynamicLabelText", \
        "CheckBoxText", "ButtonText", "SliderText", "ScrollbarText", \
        "DropdownText", "TextboxText", "DragDropText", "ProgressBarLText", \
        "ProgressBarRText"};
    const char  *bound_modes[11] = {"LabelBounds", "DynamicLabelBounds", \
        "CheckBoxBounds", "ButtonBounds", "SliderBounds", "ScrollbarBounds", \
        "DropdownBounds", "TextboxBounds", "DragDropBounds", \
        "ProgressBarBounds", "HitboxBounds"};
public:
    char        *text = NULL;
    int         unique_id = 0;
    int         gui_id = 0;
    Rectangle   bounds;
    int         text_size = 32;
    ~gui_base();
    virtual void    set_bounds(int offset_x, int offset_y, int mode, \
        mINI::INIFile file, float multiplier);
    virtual void    set_text(int id, int mode, int size, mINI::INIFile file);
};


#endif