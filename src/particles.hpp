#ifndef PARTICLES_HPP
# define PARTICLES_HPP
# include "gui/gui_base.hpp"
# include <math.h>

typedef enum particle_type { P_BASE = 0, P_DAMAGE, P_PROJECTILE } \
    particle_type;

class   particle
{
protected:
    Rectangle   bounds;
    int         original_offset;
    Color       colour = BLACK;
    bool        despawn = false;
    int         until_despawn = 60;
public:
    particle(Rectangle _bounds, Color _colour, int x_offset)
    {
        bounds = _bounds;
        original_offset = x_offset;
        bounds.x += x_offset + (UNIT_WIDTH / 2);
        bounds.y -= 8;
        colour = _colour;
    }
    virtual void    decrement(void)
    {
        if (until_despawn > 0)
        {
            until_despawn--;
            if (colour.a > 5)
                colour.a -= 5;
        }
        else
            despawn = true;
    }
    void            set_x(int x_offset) { bounds.x = x_offset; }
    virtual void    update_bounds(int x_offset)
    {
        bounds.x += (x_offset - original_offset);
        original_offset = x_offset;
    }
    Rectangle       get_bounds(void) { return(bounds); }
    bool            get_despawn(void) { return(despawn); }
    Color           get_colour(void) { return(colour); }
};
class   particle_damage : public particle
{
private:
    char    *text = NULL;
    int     text_size;
public:
    particle_damage(Rectangle _bounds, Color _colour, int damage, \
        int x_offset) : particle(_bounds, _colour, x_offset)
    {
        char    buffer[12];
        ft_itoa(damage, buffer);
        text = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));
        ft_strlcpy(text, buffer, strlen(buffer) + 2);
        text_size = 20 + (damage / 10);
    }
    ~particle_damage()
    {
        if (text)
            free (text);
    }
    void        decrement(void)
    {
        if (until_despawn > 0)
        {
            until_despawn--;
            if (colour.a > 5)
                colour.a -= 5;
            bounds.y -= 1;
        }
        else
            despawn = true;
    }
    char    *get_text(void) { return(text); }
    int     get_text_size(void) { return(text_size); }
};

class   particle_projectile : public particle
{
private:
    bool    allied = true;
    float   time = 0;
    float   angle = 0;
    int     direction = 1;
    Vector2 attacker;
    Vector2 target;
    float   theta = 0;
    float   grav = -0.81;
    float   velocity = 10;
    int     target_unique_id;
    int     attacker_unique_id;
public:
    particle_projectile(Color _colour, unit_stats atk, unit_stats tgt, \
        game_settings settings) : particle(atk.get_bounds(), _colour, \
        settings.x_offset)
    {
        allied = atk.get_allied();
        if (allied)
            direction = 1;
        else
            direction = -1;
        bounds.width = 16;
        bounds.height = 16;
        attacker.x = atk.get_bounds().x + ((256 * settings.sprite_size) / 2);
        attacker.y = bounds.y + 128 * settings.sprite_size;
        target.x = tgt.get_bounds().x + ((256 * settings.sprite_size) / 2);
        target.y = tgt.get_bounds().y + 128 * settings.sprite_size;
        target_unique_id = tgt.get_unique_id();
        attacker_unique_id = atk.get_unique_id();
        velocity = abs(tgt.get_bounds().x - atk.get_bounds().x) / \
            ((256 * settings.sprite_size) / 10) - 0.5 * ((256 * \
            settings.sprite_size) / 6) * grav;
        theta = 0.5 * asin(grav * abs(tgt.get_bounds().x - \
            atk.get_bounds().x) / (velocity * velocity));
    }
    void        update_bounds(int x_offset)
    {
        original_offset = x_offset;
    }
    void    decrement(void)
    {
        bounds.x = attacker.x + ((velocity * time * cos(theta)) * 0.5) * direction + original_offset;
        bounds.y = attacker.y + (velocity * time * sin(theta) * 2 - 0.5 * \
            grav * time * time);
        time += 1;
        if (direction == 1 && bounds.x > target.x + original_offset)
            despawn = true;
        else if (direction == -1 && bounds.x < target.x + original_offset)
            despawn = true;
    }
    Vector2 get_attacker(void) { return (attacker); }
    float   get_angle(void) { return (angle); }
    int     get_target_unique_id(void) { return (target_unique_id); }
    int     get_attacker_unique_id(void) { return (attacker_unique_id); }
};

#endif