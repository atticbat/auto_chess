#ifndef DATABASE_HPP
# define DATABASE_HPP

# include "storyboard_controls.hpp"

# define DATABASE_INPUTS 13
# define MAX_UNITS 128

void        initialise_database(std::multimap <gui_type, gui_base *> *gui);
void        set_database_boundaries(std::multimap <gui_type, gui_base *> *gui, Vector2 screen_dim);
void        draw_grid(int scroll_h_offset, int scroll_v_offset);
void        initialise_unit_db(void);
void        write_unit_db(std::multimap <gui_type, gui_base*> *gui);
void        edit_unit(std::multimap <gui_type, gui_base*> *gui);

#endif