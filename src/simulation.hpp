#ifndef SIMULATION_HPP
# define SIMULATION_HPP

# include "unit_stats.hpp"
# include "particles.hpp"

void        initialise_simulation(std::multimap <gui_type, gui_base *> *gui, \
    default_run *user, char **unit_db);
game_state  simulation(std::multimap <particle_type, particle *> *particles, \
    int *x_offset, int frame_count);
void    draw_simulation(std::multimap <particle_type, particle *> *particles, \
    int x_offset);

#endif