#ifndef USER_HPP
# define USER_HPP

# include "game_progression.hpp"
# include <stdlib.h>

class default_run
{
private:
    int     gold = 10;
    int     level = 1;
    int     exp = 0;
    int     exp_cap = 8;
    int     roster[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int     unit_exp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int     unit_max_exp[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    int     store[5] = { 0, 0, 0, 0, 0 };
    int     wins = 0;
    int     losses = 0;
    int     sprite_size = 1;
public:
    int     get_gold(void) { return (gold); }
    int     get_level(void) { return (level); }
    int     get_exp(void) { return (exp); }
    int     get_exp_cap(void) { return (exp_cap); }
    int     get_roster_slot(int slot) { return (roster[slot]); }
    int     get_unit_xp(int slot) { return (unit_exp[slot]); }
    int     get_unit_max_xp(int slot) { return (unit_max_exp[slot]); }
    int     get_store_slot(int slot) { return (store[slot]); }
    int     get_wins(void) { return (wins); }
    int     get_losses(void) { return (losses); }
    int     get_sprite_size(void) { return (sprite_size); }
    void    set_gold(int amount) { gold = amount; }
    void    add_gold(int amount) { gold += amount; }
    void    deduct_gold(int amount) { gold -= amount; }
    void    set_level(int amount) { level = amount; }
    void    add_level(void) { level++; }
    void    add_exp(int amount)
    {
        exp += amount;
        if (exp >= exp_cap)
        {
            exp = exp % exp_cap;
            exp_cap += 4;
            add_level();
        }
    }
    void    set_exp(int amount) { exp = amount; }
    void    set_exp_cap(int amount) { exp_cap = amount; }
    void    set_unit(int slot, int id) { roster[slot] = id; }
    void    set_unit_exp(int slot, int _exp) { unit_exp[slot] = _exp; }
    void    set_unit_max_exp(int slot, int _exp) { unit_max_exp[slot] = _exp; }
    void    add_unit_exp(int slot)
    {
        unit_exp[slot]++;
        if (unit_exp[slot] >= unit_max_exp[slot])
        {
            unit_exp[slot] %= unit_max_exp[slot];
            unit_max_exp[slot] = 4;
            if (roster[slot] >= 1 && roster[slot] <= 40)
                roster[slot] += 12;
            else if (roster[slot] >= 41 && roster[slot] <= 70)
                roster[slot] += 10;
        }

    }
    void    set_store (int slot, int id) { store[slot] = id; }
    void    set_wins(int amount) { wins = amount; }
    void    add_win(void) { wins++; }
    void    set_losses(int amount) { losses = amount; }
    void    add_loss(void) { losses++; }
    void    set_sprite_size(int option) { sprite_size = option; }
};

void    write_changes(default_run *user);
void    load_user(default_run *user);

#endif