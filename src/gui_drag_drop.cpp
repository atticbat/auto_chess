#include "gui_drag_drop.hpp"

gui_base    *find_gui_by_id(std::multimap <gui_type, gui_base*> *gui, \
    int id, gui_type state);

static int  check_collision(Vector2 mouse_point, std::multimap <gui_type, \
    gui_base *> *gui, int except)
{
    int id = 0;

    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
    {
        if (i->first == G_DRAG_DROP)
        {
            gui_drag_drop   *drop = dynamic_cast <gui_drag_drop *> \
                (i->second);

            if (drop && CheckCollisionPointRec(mouse_point, \
                drop->get_bounds()) && id != except && drop->get_display())
                return (drop->get_id());
            id++;
        }
    }
    return (-1);
}

static int  handle_drop(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, int overlapped, default_run *user)
{
    int swap = 0;
    gui_drag_drop   *drop = dynamic_cast <gui_drag_drop *>\
        (find_gui_by_id(gui, overlapped, G_DRAG_DROP));

    if (drop)
    {
        if (drop->get_unit_id() && !(drag->get_display()))
            return (0);
        drop->remove_sprite();
        if (drop->get_display())
            drop->generate_static_sprite(drag->get_sprite_id(), 1);
        swap = drag->get_sprite_id();
        drag->set_sprite_id(drop->get_unit_id());
        drop->set_unit_id(swap);
        if (drag->get_display())
            user->set_unit(drag->get_gui_id() - 5, drag->get_sprite_id());
        user->set_unit(drop->get_gui_id() - 5, drop->get_unit_id());
    }
    return (drop->get_unit_id());
}

static void drag_drop_controls(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, Vector2 mouse_point, default_run *user)
{
    int price_guide[33];
    price_guide[0] = 0;
    price_guide[1] = 1;
    price_guide[32] = 2;

    if (drag && CheckCollisionPointRec(mouse_point, drag->get_bounds()) && \
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && drag->get_unit_id())
    {
        drag->remove_sprite();
        drag->generate_picked_up_sprite(drag->get_sprite_id(), 1);
        drag->set_is_picked_up(true);
    }
    if (drag && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && \
        drag->get_is_picked_up())
    {
        int overlapped = check_collision(mouse_point, gui, drag->get_gui_id());

        if (price_guide[drag->get_sprite_id()] > user->get_gold() && \
            !(drag->get_display()))
            overlapped = -1;
        if (overlapped > -1)
        {
            if (!(drag->get_display()))
            {
                user->deduct_gold(price_guide[handle_drop(gui, drag, \
                    overlapped, user)]);
                user->set_store(drag->get_gui_id(), drag->get_unit_id());
            }
            else
                handle_drop(gui, drag, overlapped, user);
        }
        drag->set_is_picked_up(false);
        drag->set_unit_id(drag->get_sprite_id());
        drag->remove_sprite();
        if (drag->get_display() && drag->get_unit_id())
            drag->generate_static_sprite(drag->get_unit_id(), 1);
    }
}

void    del_sprites(std::multimap <gui_type, gui_base *> *gui)
{
    auto    range = gui->equal_range(G_DRAG_DROP);

    for (auto i = range.first; i != range.second; ++i)
    {
        gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> \
            (i->second);

        drag_drop->remove_sprite();
    }
}

void    draw_drag_drops(gui_base *gui, Vector2 mouse_point)
{
    gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> (gui);

    if (drag_drop && drag_drop->get_is_picked_up())
        drag_drop->draw_sprite(mouse_point);
    else if (drag_drop && drag_drop->get_display() && \
        drag_drop->get_sprite_id())
        drag_drop->draw_sprite((Vector2) {0, 0});
}

void    check_drag_drops(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point, default_run *user)
{
    auto range = gui->equal_range(G_DRAG_DROP);

    for (auto i = range.first; i != range.second; ++i)
    {
        gui_drag_drop   *drag = dynamic_cast <gui_drag_drop *> (i->second);

        if (drag && (drag->get_unit_id() || drag->get_sprite_id()))
            drag_drop_controls(gui, drag, mouse_point, user);
    }
}