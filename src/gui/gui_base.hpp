#ifndef GUI_HPP
# define GUI_HPP

# include <map>
# include <string>
# include "game_settings.hpp"

typedef enum gui_type {G_LABEL = 0, G_DYNAMIC_LABEL, G_CHECKBOX, G_BUTTON, \
    G_SLIDER, G_SCROLLBAR, G_DROPDOWN, G_TEXTBOX, G_DRAG_DROP, \
    G_PROGRESS_BAR, G_HITBOX} gui_type;

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
    std::string	text;
    int         unique_id;
    int         gui_id;
    Rectangle   bounds;
    int         text_size;
	gui_base();
    ~gui_base();
    virtual void    set_bounds(int offset_x, int offset_y, int mode, \
        mINI::INIFile file, float multiplier);
    virtual void    set_text(int id, int mode, int size, mINI::INIFile file);
};


#endif