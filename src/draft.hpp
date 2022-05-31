#ifndef DRAFT_HPP
# define DRAFT_HPP

# include "storyboard_controls.hpp"
# include "user.hpp"

void    initialise_draft (std::multimap <gui_type, gui_base *> *gui, \
    default_run *user);
void    reroll_shop(std::multimap <gui_type, gui_base *> *gui, default_run \
    *user);

#endif