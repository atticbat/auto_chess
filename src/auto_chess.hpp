#ifndef AUTO_CHESS_HPP
# define AUTO_CHESS_HPP

# define MAX_INPUT_CHARS 10 

typedef enum    game_state{LOADING = 0, MENU, SETTINGS, DRAFT, SIMULATION, DATABASE} game_state;
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <random>
# include <tgmath.h>
# include "../include/json_struct.h"
# include "../raylib-cpp/include/raylib-cpp.hpp"
# include "../config.hpp"
# include "sprite.hpp"
# include "input_box.hpp"

#endif