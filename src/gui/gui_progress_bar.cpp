#include "gui_progress_bar.hpp"

gui_progress_bar::gui_progress_bar(int _value, int _min, int _max) : gui_slider(_value, \
    _min, _max) { ; }

gui_progress_bar::~gui_progress_bar()
{
    if (text)
        free(text);
    if (text_right)
        free(text_right);
}

void    gui_progress_bar::set_text_right(int id, int mode, int size, mINI::INIFile file)
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

void    gui_progress_bar::increment_value(void)
{
    value++;
    if (value >= max)
    {
        value = 0;
        max = 4;
    }
}
