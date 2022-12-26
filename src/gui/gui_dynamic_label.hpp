#ifndef GUI_DYNAMIC_LABEL_HPP
# define GUI_DYNAMIC_LABEL_HPP

# include "gui_base.hpp"

class gui_dynamic_label : public gui_base
{
private:
    int     value = 0;
    int     original_length = 0;
    bool    percentage = false;
public:
    void    set_text(int id, int mode, int size, mINI::INIFile file);
	void    update_text(int _value, bool _percentage);
};

void    update_label(gui_base *gui, default_run *user);

#endif