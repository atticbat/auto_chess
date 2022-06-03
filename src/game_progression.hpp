#ifndef GAME_PROGRESSION_HPP
# define GAME_PROGRESSION_HPP

# include "../raylib-cpp/include/ini.h"
# define UNIT_WIDTH 128

void	ft_itoa(int n, char *ptr);

typedef enum    game_state{LOADING = 0, MENU, SETTINGS, DRAFT, SIMULATION, \
    DATABASE, EXIT, LOAD, BUY_XP, REROLL, APPLY, EDIT_UNIT} game_state;

game_state  parse_destination(int id, mINI::INIFile file);

#endif