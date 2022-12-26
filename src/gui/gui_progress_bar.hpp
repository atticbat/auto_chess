#ifndef GUI_PROGRESS_BAR_HPP
# define GUI_PROGRESS_BAR_HPP

# include "gui_slider.hpp"

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
        ft_strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
        text_right = ptr;
    }
    char    *get_text_right(void) { return (text_right); }
    void    increment_value(void)
    {
        value++;
        if (value >= max)
        {
            value = 0;
            max = 4;
        }
    }
};

#endif