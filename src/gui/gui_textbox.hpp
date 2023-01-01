#ifndef GUI_TEXTBOX_HPP
# define GUI_TEXTBOX_HPP

# include "gui_base.hpp"

class gui_textbox : public gui_base
{
private:
    const int   db_max_input[13] = {3, 1, 2, 2, 2, 4, 5, 4, 4, 4, 1, 4, 4};
    int         max_input;
public:
    bool        edit_mode;
    int         input_count;
	gui_textbox();
    void    set_text(int id, int size);
    bool    check_if_max(void);
    void    add_letter(char letter);
    void    delete_letter(void);
};

void        input_status_check(gui_textbox *textbox, Vector2 mousePoint);
void        check_textboxes(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point);
void        draw_textbox(gui_base *gui);

#endif