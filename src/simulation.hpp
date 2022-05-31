#ifndef SIMULATION_HPP
# define SIMULATION_HPP

# include "storyboard_controls.hpp"
# include "user.hpp"

void        initialise_simulation(std::multimap <gui_type, gui_base *> *gui, \
    default_run *user);
game_state  simulation(int *x_offset);
void        draw_simulation(int x_offset);

#endif