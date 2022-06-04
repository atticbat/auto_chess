#include "simulation.hpp"
#include <algorithm>
#include <random>

unit_stats  battle[56];
int         move_order[56];

void    initialise_simulation(std::multimap <gui_type, gui_base *> *gui, \
    std::map <int, sprite_multi *> *sprites, default_run *user, char **unit_db)
{
    std::random_device rnd;
    std::mt19937 g(rnd());
    mINI::INIFile file ("data/simulation_gui.ini");

    for (int i = 0; i < 8; i++)
    {
        if (user->get_roster_slot(i))
        {
            battle[16 + i].initialise_unit(user->get_roster_slot(i), unit_db, \
                true, i);
            sprite_multi    *sprite = new sprite_multi(\
                battle[16 + i].get_unit_id(), 9, 1, file);

            sprites->insert(std::pair <int, sprite_multi *> \
                (battle[16 + i].get_unique_id(), sprite));
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (user->get_roster_slot(i))
        {
            battle[40 - i].initialise_unit(user->get_roster_slot(i), unit_db, \
                false, i);
            sprite_multi    *sprite = new sprite_multi(\
                battle[40 - i].get_unit_id(), 9, 5, file);

            sprites->insert(std::pair <int, sprite_multi *> \
                (battle[40 - i].get_unique_id(), sprite));
        }
    }
    for (int i = 0; i < 56; i++)
        move_order[i] = i;
    std::shuffle(&move_order[0], &move_order[55], g);
}

static int  scroll_controls(int x_offset)
{
    if (IsKeyPressed(KEY_LEFT) && x_offset < 0)
        return (24);
    else if (IsKeyDown(KEY_LEFT) && x_offset < 0)
        return (12);
    if (IsKeyPressed(KEY_RIGHT) && x_offset > -5248)
        return (-24);
    else if (IsKeyDown(KEY_RIGHT) && x_offset > -5248)
        return (-12);
    return (0);
}

static void unit_movement(int i, sprite_multi *sprite)
{
    if (!(battle[i].get_is_moving()) && battle[i].get_unit_id() \
        && battle[i + battle[i].get_direction()].get_unit_id() == 0)
    {
        battle[i].set_to_move(128);
        battle[i].set_is_moving(true);
        std::swap(battle[i], battle[i + \
            battle[i].get_direction()]);
        if (sprite->get_animation() != 2 && sprite->get_animation() != 1)
            sprite->change_animation(2);
    }
    else if (battle[i].get_to_move() == 0 && !(battle[i].get_is_moving()) && \
        sprite->get_animation() == 2)
        sprite->change_animation(0);
}

static void perform_attack(std::multimap <particle_type, particle *> \
    *particles, int attacker, int target, int x_offset)
{
        particle_damage *label;
        if (battle[target].get_allied())
            label = new particle_damage(battle[target].get_bounds(), \
                MAROON, battle[target].deal_damage(\
                battle[attacker].conduct_attack()), x_offset);
        else
            label = new particle_damage(battle[target].get_bounds(), \
                DARKBLUE, battle[target].deal_damage(\
                battle[attacker].conduct_attack()), x_offset);
        particles->insert(std::pair<particle_type, particle_damage *> \
            (P_DAMAGE, label)); 
}

static void unit_melee_attack(std::multimap <particle_type, particle *> \
    *particles, int i, int x_offset, sprite_multi *sprite)
{
    if (battle[i].get_unit_id() && battle[i].get_perform_attack() && \
        battle[i].get_allied() != battle[i + battle[i].get_direction()].\
        get_allied() && battle[i + battle[i].get_direction()].get_unit_id())
    {
        perform_attack(particles, i, i + battle[i].get_direction(), x_offset);
        sprite->change_animation(1);
    }
}

static void unit_ranged_attack(std::multimap <particle_type, particle *> \
    *particles, int i, int x_offset, sprite_multi *sprite)
{
    if (battle[i].get_unit_id() && battle[i].get_max_range() > 1 && \
        battle[i].get_perform_attack())
    {
        std::vector<int> viable_targets;
        for (int k = battle[i].get_max_range(); k > \
            battle[i].get_dead_zone(); k--)
        {
            if (battle[i + battle[i].get_direction() * \
                k].get_unit_id() && battle[i + battle[i].get_direction() * \
                k].get_allied() != battle[i].get_allied())
                viable_targets.push_back(i + battle[i].get_direction() * k);
        }
        if (!(viable_targets.empty()))
        {
            std::random_shuffle(viable_targets.begin(), \
                viable_targets.end());
            particle_projectile *projectile = new particle_projectile(BLACK, \
                battle[i], battle[viable_targets.front()], x_offset + 64);

            particles->insert(std::pair<particle_type, particle_projectile *> \
                (P_PROJECTILE, projectile));
            battle[i].set_projectile_mid_flight(true);
            sprite->change_animation(1);
        }
    }
}

static int  find_unit_by_unique_id(int unique_id)
{
    for (int i = 0; i < 56; i++)
    {
        if (battle[i].get_unique_id() == unique_id)
            return (i);
    }
    return (-1);
}

game_state  simulation(std::multimap <particle_type, particle *> *particles, \
    std::map <int, sprite_multi *> *sprites, int *x_offset, int frame_count)
{
    *x_offset += scroll_controls(*x_offset);
    if (frame_count % 8 == 0)
    {
        for (int i = 0; i < 56; i++)
        {
            int j = move_order[i];
            auto    search = sprites->find(battle[j].get_unique_id());
            if (search != sprites->end())
            {
                unit_movement(j, search->second);
                battle[j].increase_atk_gauge();
                unit_melee_attack(particles, j, *x_offset, search->second);
                if (!(battle[j].get_projectile_mid_flight()))
                    unit_ranged_attack(particles, j, *x_offset, search->second);
                if (battle[j].get_is_dead())
                {
                    battle[j].destroy_unit();
                    search->second->set_despawn();
                }
            }
        }
        for (auto i = sprites->begin(); i != sprites->end(); ++i)
            i->second->increment_state();
    }
    for (int i = 0; i < 56; i++)
    {
        battle[i].adjust_sprite();
        battle[i].set_gauge_bounds();
    }
    for (std::multimap <particle_type, particle *>::iterator i = \
        particles->begin(); i != particles->end(); ++i)
    {
        switch (i->first)
        {
            case P_DAMAGE:
            {
                particle_damage *label = static_cast <particle_damage *> \
                    (i->second);
        
                if (label)
                {
                    label->decrement();
                    label->update_bounds(*x_offset);
                }
            } break ;
            case P_PROJECTILE:
            {
                particle_projectile *projectile = static_cast \
                    <particle_projectile *> (i->second);

                if (projectile)
                {
                    projectile->decrement();
                    if (projectile->get_despawn())
                    {
                        int atk_index = find_unit_by_unique_id(\
                            projectile->get_attacker_unique_id());
                        int tgt_index = find_unit_by_unique_id(\
                            projectile->get_target_unique_id());
                        if (atk_index > 0 && tgt_index > 0)
                        {
                            perform_attack(particles, atk_index, \
                                tgt_index, *x_offset);
                            battle[atk_index].set_projectile_mid_flight(false);
                        }
                    }
                    projectile->update_bounds(*x_offset);
                }
            } break ;
            default : break ;
        } 
    }
    return (SIMULATION);
}

static void despawn_particles(std::multimap <particle_type, particle *> *particles)
{
    for (std::multimap <particle_type, particle *>::iterator i = \
        particles->begin(); i != particles->end(); )
    {
        if (i->second->get_despawn())
        {
            if (i->first == P_DAMAGE)
            {
                particle_damage *label = static_cast <particle_damage *> \
                    (i->second);
                if (label)
                    delete(label);
            }
            else
                delete(i->second);
            i = particles->erase(i);
        }
        else
            i++;
    }
}

void    draw_simulation(std::multimap <particle_type, particle *> *particles, \
    std::map <int, sprite_multi *> *sprites, int x_offset)
{
    for (int i = 0; i < 56; i++)
    {
        if (battle[i].get_unit_id())
        {
            for (int j = 0; j < 3; j++)
            {
                DrawRectangle(battle[i].get_gauge_bounds(j).x + x_offset, \
                    battle[i].get_gauge_bounds(j).y, \
                    battle[i].get_gauge_bounds(j).width, \
                    battle[i].get_gauge_bounds(j).height, \
                    battle[i].get_gauge_colour(j));
            }
        }
        // if (battle[i].get_unit_id() && battle[i].get_allied())
        //     DrawRectangle(battle[i].get_bounds().x + x_offset, \
        //         battle[i].get_bounds().y, battle[i].get_bounds().width, \
        //         battle[i].get_bounds().height, BLUE);
        // else if (battle[i].get_unit_id())
        //     DrawRectangle(battle[i].get_bounds().x + x_offset, \
        //         battle[i].get_bounds().y, battle[i].get_bounds().width, \
        //         battle[i].get_bounds().height, RED); 
        if (battle[i].get_unit_id())
        {
            auto    search = sprites->find(battle[i].get_unique_id());

            if (search != sprites->end())
                DrawTextureRec(search->second->get_image(), search->second->get_source(), \
                    (Vector2) { battle[i].get_bounds().x + x_offset - 96, battle[i].get_bounds().y }, WHITE);
        }
        DrawText(TextFormat("%i", move_order[i]), 128 * i + x_offset + 4, \
            404, 24, BLACK);
        DrawRectangleLines(128 * i + x_offset, 400, 128, 256, BLACK);
    }
    for (std::multimap <particle_type, particle *>::iterator i = \
        particles->begin(); i != particles->end(); ++i)
    {
        switch (i->first)
        {
            case P_DAMAGE:
            {
                particle_damage *label = static_cast <particle_damage *> \
                    (i->second);
        
                if (label)
                {
                    DrawText(label->get_text(), label->get_bounds().x, \
                        label->get_bounds().y, label->get_text_size(), \
                        label->get_colour());
                }
            } break ;
            case P_PROJECTILE:
            {
                particle_projectile *projectile = static_cast \
                    <particle_projectile *> (i->second);

                if (projectile)
                {
                    DrawRectangle(projectile->get_bounds().x, \
                        projectile->get_bounds().y, projectile->get_bounds().width, \
                        projectile->get_bounds().height, projectile->get_colour());
                }
            } break ;
            default : break ;
        }
    }
    despawn_particles(particles);
}