#ifndef GAME_PROGRESSION_HPP
# define GAME_PROGRESSION_HPP

# include "../raylib-cpp/include/ini.h"

void	ft_itoa(int n, char *ptr);

typedef enum    game_state{LOADING = 0, MENU, SETTINGS, DRAFT, SIMULATION, \
    DATABASE, EXIT, LOAD, BUY_XP, REROLL, APPLY, EDIT_UNIT} game_state;

typedef enum gui_type {G_LABEL = 0, G_DYNAMIC_LABEL, G_CHECKBOX, G_BUTTON, \
    G_SLIDER, G_SCROLLBAR, G_DROPDOWN, G_TEXTBOX, G_DRAG_DROP, \
    G_PROGRESS_BAR} gui_type;

game_state  parse_destination(int id, mINI::INIFile file);

#endif