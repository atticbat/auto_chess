#include "gui_base.hpp"

gui_base::gui_base()
{
	unique_id = 0;
	gui_id = 0;
	text_size = 32;
	//could add bounds & text here too
}

gui_base::~gui_base()
{
}

void	gui_base::set_bounds(int offset_x, int offset_y, int mode, \
    mINI::INIFile file, float multiplier)
{
    mINI::INIStructure ini;
    float param[4];
    int i;
    std::string	str;
    int from = 0;
    int to = 0;
    char    c[5];

    ft_itoa(gui_id, c);
    file.read(ini);
    i = 0;
    str = ini.get(bound_modes[mode]).get(c);
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
    bounds = (Rectangle) { (param[0]) * multiplier, (param[1] \
        ) * multiplier, param[2] * multiplier, param[3] * \
        multiplier };
}

void    gui_base::set_text(int id, int mode, int size, mINI::INIFile file)
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
    ft_strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
    text = ptr;
}