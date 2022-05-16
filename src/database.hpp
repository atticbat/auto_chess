#ifndef DATABASE_HPP
# define DATABASE_HPP

# include "sprite.hpp"
# include "input_box.hpp"

# define DATABASE_BUTTONS 2
# define DATABASE_INPUTS 13
# define MAX_UNITS 128

sprite      *initialise_db(int *unique_id, int offset, int screen_width, int screen_height);
game_state  check_database(sprite *btn, input_box *in_db, Vector2 mousePoint, int *frame_count);
void        draw_database(sprite *btn, input_box *in_db, int screen_width, int screen_height, int frame_count);
input_box   *initialise_db_in(int screen_width);
void        draw_grid(int screen_offset);

#endif