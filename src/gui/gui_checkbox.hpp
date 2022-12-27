#ifndef GUI_CHECKBOX_HPP
# define GUI_CHECKBOX_HPP

# include "gui_base.hpp"

class gui_checkbox : public gui_base
{
public:
    bool    		checked = false;
};

bool        check_checkbox(gui_base *gui);
void        set_checkbox(gui_base *gui, bool checked);

#endif