#ifndef GUI_DRAG_DROP_HPP
# define GUI_DRAG_DROP_HPP

# include "gui_base.hpp"

class gui_drag_drop : public gui_base
{
private:
    bool        is_picked = false;
    bool        display = false;
    int         unit_id = 0;
    sprite_base *sprite = NULL;
public:
    void        set_is_picked_up (bool _is_picked) { is_picked = _is_picked; }
    bool        get_is_picked_up (void) { return (is_picked); }
    void        generate_picked_up_sprite (int id, int frames, mINI::INIFile \
        file)
    {
        sprite = new sprite_picked_up(unit_id, frames, 0, file);
        unit_id = 0;
    }
    void        generate_static_sprite (int id, int frames, mINI::INIFile file)
    {
        sprite = new sprite_base(id, frames, 1, file);
    }
    void        remove_sprite(void)
    {
        if (sprite)
        {
            delete (sprite);
            sprite = NULL;
        }
    }
    void        draw_sprite(Vector2 point, float scale, bool drag)
    {
        if (drag)
        {
            sprite_picked_up    *picked_up = static_cast <sprite_picked_up *> (sprite);

            if (picked_up)
                DrawTexturePro(picked_up->get_image(), picked_up->get_source(), \
                    picked_up->get_boundaries(point, scale), \
                    picked_up->get_offset_location(scale), 0, RAYWHITE);
        }
        else
            DrawTexturePro(sprite->get_image(), sprite->get_source(), \
                sprite->get_boundaries(bounds, scale), \
                sprite->get_offset_location(bounds, scale), 0, RAYWHITE);
    }
    void        set_unit_id(int id) { unit_id = id; }
    int         get_unit_id(void) { return (unit_id); }
    int         get_sprite_id(void)
    {
        if (sprite)
            return (sprite->get_unit_id());
        return (0);
    }
    void        increment_state(void)
    {
        if (sprite)
            sprite->increment_state();
    }
    void        set_sprite_id(int id) { sprite->set_unit_id(id); }
    void        set_display(bool _display) { display = _display; }
    bool        get_display(void) { return (display); }

};



void    check_drag_drops(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point, default_run *user);
void    del_sprites(std::multimap <gui_type, gui_base *> *gui);
void    draw_drag_drops(gui_base *gui, game_settings settings);

#endif