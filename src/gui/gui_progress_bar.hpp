#ifndef GUI_PROGRESS_BAR_HPP
# define GUI_PROGRESS_BAR_HPP

# include "gui_slider.hpp"

class gui_progress_bar : public gui_slider
{
public:
    char    *text_right = NULL;
    gui_progress_bar(int _value, int _min, int _max);
    ~gui_progress_bar();
    void    set_text_right(int id, int mode, int size, mINI::INIFile file);
    void    increment_value(void);
};

#endif