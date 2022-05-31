#ifndef UNIT_STATS_HPP
# define UNIT_STATS_HPP

# include <stdlib.h>
char    **ft_split(char *str, char delimeter);

class unit_stats
{
private:
    int     unique_id;
    int     unit_id;
    int     attack;
    int     health;
    int     max_health;
    float   attack_speed;
    float   defense;
    int     range;
    int     ability_power;
    int     ability_cost;
    int     gauge;
    int     gauge_current = 0;
    bool    allied = true;
    int     direction;
    int     position;
    int     to_move;
    int     movement_speed;
    bool    perform_attack = false;
    bool    is_dead = false;
public:
    unit_stats (int id, char **unit_db)
    {
        static int  _unique_id = 0;
        char        *line = unit_db[id];
        char        **split = ft_split(line, ',');

        unit_id = id;
        unique_id = _unique_id;
        _unique_id++;
        attack = atoi(split[5]);
        health = atoi(split[6]);
        max_health = health;
        attack_speed = (float) atoi(split[7]);
        defense = (float) atoi(split[9]);
        range = atoi(split[10]);
        ability_power = atoi(split[8]);
        ability_cost = atoi(split[11]);
        gauge = atoi(split[12]);
        for (int i = 0; i < 12; i++)
        {
            free(split[i]);
        }
        free (split);
    }
    int     get_unique_id(void) { return (unique_id); }
    int     get_unit_id(void) { return (unit_id); }
    int     get_attack(void) { return (attack); }
    int     get_health(void) { return (health); }
    int     get_max_health(void) { return (max_health); }
    int     get_attack_speed(void) { return (attack_speed); }
    int     get_defense(void) { return (defense); }
    int     get_range(void) { return (range); }
    int     get_ability_power(void) { return (ability_power); }
    int     get_ability_cost(void) { return (ability_cost); }
    int     get_gauge(void) { return (gauge); }
    int     get_gauge_current(void) { return (gauge_current); }
    bool    get_allied(void) { return (allied); }
    int     get_direction(void) { return (direction); }
    int     get_position(void) { return (position); }
    int     get_to_move(void) { return (to_move); }
    int     get_movement_speed(void) { return (movement_speed); }
    bool    get_perform_attack(void) { return (perform_attack); }
    bool    get_is_dead(void) { return (is_dead); }

    void    multiplier_atk(int amount) { attack *= amount; }
    void    increase_atk(int amount) { attack += amount; }
    void    multiplier_hp(int amount) { health *= amount; }
    void    increase_hp(int amount) { health += amount; }
    void    multiplier_max_hp(int amount) { max_health *= amount; }
    void    increase_max_hp(int amount) { max_health += amount; }
    void    deal_damage(int amount)
    {
        health -= (amount / defense);
        if (health < 0)
            is_dead = true;
    }
    void    multiplier_atk_spd(int amount) { attack_speed *= amount; }
    void    multiplier_def(int amount) { defense *= amount; }
    void    multiplier_ap(int amount) { ability_power *= amount; }
    void    increase_ap(int amount) { ability_power += amount; }
    void    increase_gauge(int amount)
    {
        gauge_current += amount;
        if (gauge_current >= gauge)
        {
            gauge_current = 0;
            perform_attack = true;
        }
    }
    void    reset_gauge(void) { gauge_current = 0; }
    void    set_allied(bool _allied) { allied = _allied; }
    void    set_direction(int dir) { direction = dir; }
    void    set_position(int pos) { position = pos; }
    void    set_to_move(int amount) { to_move = amount; }
    void    set_move_speed(int amount) { movement_speed = amount; }
    void    reset_attack(void) { perform_attack = false; }
};

#endif