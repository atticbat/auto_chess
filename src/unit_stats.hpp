#ifndef UNIT_STATS_HPP
# define UNIT_STATS_HPP

# include "gui.hpp"
// # include "gauge.hpp"

class unit_stats
{
private:
    Color       gauge_colours[3] = { GREEN, BLUE, GRAY };
    Rectangle   gauge_bounds[3];
    float       gauges[3] = { 0, 0, 0 };
    float       max_gauges[3] = { 100, 100, 100 };
    Rectangle   bounds;
    int         unique_id = 0;
    int         unit_id = 0;
    int         attack = 0;
    int         health = 0;
    int         max_health = 0;
    float       attack_speed = 0;
    float       attack_gauge = 0;
    bool        perform_attack = false;
    bool        projectile_mid_flight = false;
    float       defense = 0;
    int         max_range = 1;
    int         dead_zone = 0;
    int         ability_power = 0;
    int         ability_cost = 0;
    int         ap_gauge_max = 0;
    int         ap_gauge = 0;
    bool        cast_spell = false;
    bool        allied = true;
    int         direction;
    int         position;
    int         to_move;
    int         movement_speed = 4;
    bool        is_moving = false;
    bool        is_dead = false;
public:
    void    re_init(void)
    {
        for (int i = 0; i < 3; i++)
        {
            gauges[i] = 0;
            max_gauges[i] = 100;
        }
        unique_id = 0;
        unit_id = 0;
        perform_attack = false;
        projectile_mid_flight = false;
        cast_spell = false;
        allied = true;
        to_move = 0;
        is_moving = false;
        is_dead = false;
    }
    void    initialise_unit (int id, char **unit_db, bool ally, int pos, float scale)
    {

        static int  _unique_id = 1;
        char        *line = unit_db[id];
        char        **split = ft_split(line, ',');
        int         range;

        unit_id = id;
        unique_id = _unique_id;
        allied = ally;
        _unique_id++;
        if (allied)
        {
            bounds = (Rectangle) { (float) (16 + pos) * 256 * scale, 400, 256 \
                * scale, 512 * scale };
            direction = 1;
        }
        else
        {
            bounds = (Rectangle) { (float) (40 - pos) * 256 * scale, 400, 256 \
                * scale, 512 * scale };
            direction = -1;
        }
        attack = atoi(split[5]);
        gauges[0] = atoi(split[6]);
        max_gauges[0] = gauges[0];
        attack_speed = (float) atoi(split[7]) / 10;
        defense = (float) atoi(split[9]) / 10;
        range = atoi(split[10]);
        switch (range)
        {
            case 2:
            {
                max_range = 2;
                dead_zone = 0;
            } break ;
            case 3:
            {
                max_range = 4;
                dead_zone= 0;
            } break ;
            case 4:
            {
                max_range = 6;
                dead_zone = 2;
            } break ;
            case 5:
            {
                max_range = 8;
                dead_zone = 3;
            } break ;
            default: break ;
        }
        ability_power = atoi(split[8]);
        ability_cost = atoi(split[11]);
        max_gauges[1] = atoi(split[12]);
        for (int i = 0; i < 13; i++)
            free(split[i]);
        free (split);


    }
    Rectangle   get_gauge_bounds(int index)
    {
        return (gauge_bounds[index]);
    }
    Color       get_gauge_colour(int index)
    {
        return (gauge_colours[index]);
    }
    Rectangle   get_bounds(void) { return (bounds); }
    int         get_unique_id(void) { return (unique_id); }
    int         get_unit_id(void) { return (unit_id); }
    int         get_attack(void) { return (attack); }
    int         get_health(void) { return (gauges[0]); }
    int         get_max_health(void) { return (max_gauges[0]); }
    float       get_attack_speed(void) { return (attack_speed); }
    float       get_attack_gauge(void) { return (gauges[2]); }
    float       get_defense(void) { return (defense); }
    int         get_max_range(void) { return (max_range); }
    int         get_dead_zone(void) { return (dead_zone); }
    int         get_ability_power(void) { return (ability_power); }
    int         get_ability_cost(void) { return (ability_cost); }
    int         get_ap_gauge_max(void) { return (max_gauges[1]); }
    int         get_ap_gauge(void) { return (gauges[1]); }
    bool        get_allied(void) { return (allied); }
    int         get_direction(void) { return (direction); }
    int         get_position(void) { return (position); }
    int         get_to_move(void) { return (to_move); }
    int         get_movement_speed(void) { return (movement_speed); }
    bool        get_perform_attack(void) { return (perform_attack); }
    bool        get_projectile_mid_flight(void) { return (projectile_mid_flight); }
    bool        get_cast_spell(void) { return (cast_spell); }
    bool        get_is_moving(void) { return (is_moving); }
    bool        get_is_dead(void) { return (is_dead); }
    void        set_gauge_bounds(float scale)
    {
        for (int i = 0; i < 3; i++)
        {
            gauge_bounds[i] = (Rectangle) { bounds.x, bounds.y + 512 * scale \
                + (i * 16), (gauges[i] / max_gauges[i]) * (248 * scale), 16 };
        }
    }
    void        multiplier_atk(int amount) { attack *= amount; }
    void        increase_atk(int amount) { attack += amount; }
    void        multiplier_hp(int amount) { gauges[0] *= amount; }
    void        increase_hp(int amount) { gauges[0] += amount; }
    void        multiplier_max_hp(int amount) { max_gauges[0] *= amount; }
    void        increase_max_hp(int amount) { max_gauges[0] += amount; }
    int         deal_damage(int amount)
    {
        gauges[0] -= (amount / defense);
        increase_ap_gauge(5);
        if (gauges[0] < 0)
            is_dead = true;
        return ((int) amount / defense);
    }
    void        multiplier_atk_spd(int amount) { attack_speed *= amount; }
    void        increase_atk_gauge(void)
    {
        if (!(perform_attack))
            gauges[2] += attack_speed;
        if (gauges[2] >= max_gauges[2])
        {
            gauges[2] = max_gauges[2];
            perform_attack = true;
        }
    }
    int         conduct_attack(void)
    {
        gauges[2] = 0;
        perform_attack = false;
        increase_ap_gauge(10);
        return (attack);
    }
    void        set_projectile_mid_flight(bool flying) { projectile_mid_flight = flying; }
    void        multiplier_def(int amount) { defense *= amount; }
    void        multiplier_ap(int amount) { ability_power *= amount; }
    void        increase_ap(int amount) { ability_power += amount; }
    void        increase_ap_gauge(int amount)
    {
        if (!(cast_spell))
            gauges[1] += amount;
        if (gauges[1] >= max_gauges[1])
        {
            gauges[1] = max_gauges[1];
            cast_spell = true;
        }
    }
    int         conduct_spell(void)
    {
        gauges[1] = 0;
        cast_spell = false;
        return (ability_power);
    }
    void        set_allied(bool _allied) { allied = _allied; }
    void        set_direction(int dir) { direction = dir; }
    void        set_position(int pos) { position = pos; }
    void        set_to_move(int amount) { to_move = amount; }
    void        set_move_speed(int amount) { movement_speed = amount; }
    void        set_is_moving(bool moving) { is_moving = moving; }
    void        adjust_sprite(void)
    {
        if (to_move > 0)
        {
            bounds.x += (direction * movement_speed);
            to_move -= movement_speed;
        }
        if (to_move <= 0)
            is_moving = false;
    }
    void        destroy_unit(void) { unit_id = 0; }
};

#endif