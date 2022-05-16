#ifndef INPUT_BOX_HPP
# define INPUT_BOX_HPP

# include "../raylib-cpp/include/raylib-cpp.hpp"
# include "../config.hpp"
# define MAX_INPUT_CHARS 5

class input_box
{
    private:
        int         max_input;
    public:
        char        input[MAX_INPUT_CHARS + 1];
        int         count;
        Rectangle   box;
        bool        on_text;
        void        initialise(float off_x, float off_y, int max)
        {
            input[0] = '\0';
            count = 0;
            box = { off_x, off_y, (float) 128, (float) 40 };
            on_text = false;
            max_input = max;
        }
        int         check_if_max(void)
        {
            if (count < max_input)
                return (1);
            return (0);
        }
};

#endif