#ifndef INPUT_BOX_HPP
# define INPUT_BOX_HPP

# include "auto_chess.hpp"
// # define db_names {"ID", "Cost", "Tag 1", "Tag 2", "Tag 3", "Attack", "Health", "Atk Spd", "Abl Pwr", "Defense", "Range", "Abl Cost", "Abl Gauge"}


class input_box
{
    public:
        char        input[MAX_INPUT_CHARS + 1];
        int         count;
        Rectangle   box;
        bool        on_text;
        void        initialise(float off_x, float off_y)
        {
            input[0] = '\0';
            count = 0;
            box = { off_x, off_y, (float) 192, (float) 40 };
            on_text = false;
        }
};

#endif