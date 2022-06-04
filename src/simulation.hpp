#ifndef SIMULATION_HPP
# define SIMULATION_HPP

# include "unit_stats.hpp"
# include "particles.hpp"

void    initialise_simulation(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, default_run *user, char **unit_db);
game_state  simulation(std::multimap <particle_type, particle *> *particles, \
    std::map <int, sprite_multi *> *sprites, int *x_offset, int frame_count);
void    draw_simulation(std::multimap <particle_type, particle *> *particles, \
    std::map <int, sprite_multi *> *sprites, int x_offset);

#endif