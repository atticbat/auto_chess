#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "particles.hpp"
#include "storyboard_controls.hpp"
#include "unit_stats.hpp"

void initialise_sim_gui(std::multimap<gui_type, gui_base *> *gui);
void initialise_simulation(std::map<int, sprite_multi *> *sprites,
                           default_run *user, float sprite_size,
                           char **unit_db);
void simulation(std::multimap<particle_type, particle *> *particles,
                std::map<int, sprite_multi *> *sprites, game_settings *settings,
                std::multimap<gui_type, gui_base *> *gui);
void draw_simulation(std::multimap<particle_type, particle *> *particles,
                     std::map<int, sprite_multi *> *sprites,
                     game_settings settings);

#endif