#ifndef GUI_TEXTBOX_HPP
# define GUI_TEXTBOX_HPP

# include "gui_base.hpp"

class gui_textbox : public gui_base
{
private:
    int         max_input = 5;
    bool        edit_mode = false;
    int         input_count = 0;
    const int   db_max_input[13] = {3, 1, 2, 2, 2, 4, 5, 4, 4, 4, 1, 4, 4};
public:
    void    set_text(int id, int size)
    {
        gui_id = id;
        text_size = size;
        max_input = db_max_input[id];
        text = (char *) malloc (sizeof(char) * (max_input + 1));
    }
    void    set_edit_mode(bool mode) { edit_mode = mode; }
    bool    get_edit_mode(void) { return(edit_mode); }
    bool    check_if_max(void)
    {
        if (input_count == max_input)
            return (true);
        return (false);
    }
    void    add_letter(char letter)
    {
        if (!check_if_max())
        {
            text[input_count] = letter;
            input_count++;
            text[input_count] = '\0';
        }
    }
    void    delete_letter(void)
    {
        if (input_count > 0)
        {
            input_count--;
            text[input_count] = '\0';
        }
    }
};

void        input_status_check(gui_textbox *textbox, Vector2 mousePoint);
void        check_textboxes(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point);
void        draw_textbox(gui_base *gui);

#endif