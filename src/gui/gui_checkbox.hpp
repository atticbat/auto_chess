#ifndef GUI_CHECKBOX_HPP
# define GUI_CHECKBOX_HPP

# include "gui_base.hpp"

class gui_checkbox : public gui_base
{
protected:
    bool    checked = false;
public:
    virtual void    set_checked(bool _checked) { checked = _checked; }
    bool            get_checked(void) { return (checked); }
};

bool        check_checkbox(gui_base *gui);
void        set_checkbox(gui_base *gui, bool checked);

#endif