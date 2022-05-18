#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "sprite.hpp"
# include "../raylib-cpp/include/raygui.h"
# include "../raylib-cpp/include/ini.h"
# include <stdlib.h>
# include <stdio.h>
# define RAYGUI_IMPLEMENTATION

# define SETTINGS_BUTTONS 2

class gui_dropdown
{
private:
    const char  *i_to_c[4] = {"0", "1", "2", "3"};
public:
    Rectangle   bounds;
    char        *names;
    void        set_dropdown_bounds(int offset_x, int offset_y, int id)
    {
        mINI::INIFile file ("data/settings_gui.ini");
        mINI::INIStructure ini;
        float param[4];
        int i;

        file.read(ini);
        i = 0;
        while (i < 4)
        {
            param[i] = 0;
            i++;
        }
        i = 0;
        char    str[16];
        memcpy(str, ini.get("DropdownBounds").get(i_to_c[id]).c_str(), 16);
        int from = 0;
        int to = 0;
        while (i < 4)
        {
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
        bounds = (Rectangle) { param[0] + offset_x, param[1] + offset_y, param[2], param[3] };
    }
    void    set_name(char id)
    {
        char                *ptr;
        size_t              len;
        mINI::INIFile       file ("data/settings_gui.ini");
        mINI::INIStructure  ini;

        file.read(ini);
        len = ini.get("DropdownText").get(&id).size();
        ptr = (char *) malloc (sizeof(char) * len);
        strlcpy(ptr, ini.get("DropdownText").get(&id).c_str(), len + 1);
        names = ptr;
    }
};

game_state  check_settings(sprite *btn, Vector2 mousePoint);
sprite  *initialise_settings(int *unique_id, int offset, int screen_width, int screen_height);
void    draw_settings(sprite *btn, int screen_width, int screen_height);

#endif