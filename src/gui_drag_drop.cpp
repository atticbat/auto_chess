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

static void swap_xp_bars(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, gui_drag_drop *drop, default_run *user)
{
    int swap = 0;

    if (drop && drop->get_display())
    {
        gui_progress_bar    *drag_bar = dynamic_cast \
            <gui_progress_bar *>(find_gui_by_id(gui, \
            drag->get_id() + 8, G_PROGRESS_BAR));
        gui_progress_bar    *drop_bar = dynamic_cast \
            <gui_progress_bar *>(find_gui_by_id(gui, \
            drop->get_id() + 8, G_PROGRESS_BAR));
        if (drag_bar && drop_bar)
        {
            swap = drag_bar->get_value();
            drag_bar->set_value(drop_bar->get_value());
            drop_bar->set_value(swap);
            swap = drag_bar->get_max();
            drag_bar->set_max(drop_bar->get_max());
            drop_bar->set_max(swap);
            swap = user->get_unit_xp(drag->get_gui_id() - 5);
            user->set_unit_exp(drag->get_gui_id() - 5, \
                user->get_unit_xp(drop->get_gui_id() - 5));
            user->set_unit_exp(drop->get_gui_id() - 5, swap);
            swap = user->get_unit_max_xp(drag->get_gui_id() - 5);
            user->set_unit_max_exp(drag->get_gui_id() - 5, \
                user->get_unit_max_xp(drop->get_gui_id() - 5));
            user->set_unit_max_exp(drop->get_gui_id() - 5, swap);
        }
    }
}

static bool check_same_unit(int drag_unit, int drop_unit)
{
    if (drag_unit >= 1 && drag_unit <= 40)
    {
        if (drag_unit == drop_unit)
            return (true);
        else if (drag_unit + 12 == drop_unit)
            return (true);
    }
    else if (drag_unit >= 41 && drag_unit <= 70)
    {
        if (drag_unit == drop_unit)
            return (true);
        else if (drag_unit + 10 == drop_unit)
            return (true);
    }
    else if (drag_unit >= 71 && drag_unit <= 100)
    {
        if (drag_unit == drop_unit)
            return (true);
        else if (drag_unit + 9 == drop_unit)
            return (true);
    }
    else if (drag_unit >= 101 && drag_unit <= 120)
    {
        if (drag_unit == drop_unit)
            return (true);
        else if (drag_unit + 6 == drop_unit)
            return (true);
    }
    return (false);
}

static void increase_exp(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, gui_drag_drop *drop, default_run *user)
{
    gui_progress_bar    *bar = dynamic_cast <gui_progress_bar *> \
        (find_gui_by_id(gui, drop->get_id() + 8, G_PROGRESS_BAR));

    if (bar)
    {
        bar->increment_value();
        drop->set_unit_id(0);
        user->add_unit_exp(drop->get_gui_id() - 5);
        drag->set_sprite_id(user->get_roster_slot(\
            drop->get_gui_id() - 5));
    }
}

static int  handle_drop(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, int overlapped, default_run *user)
{
    int swap = 0;
    mINI::INIFile file ("data/draft_gui.ini");
    gui_drag_drop   *drop = dynamic_cast <gui_drag_drop *>\
        (find_gui_by_id(gui, overlapped, G_DRAG_DROP));

    if (drop)
    {
        if (drop->get_unit_id())
        {
            if (!(check_same_unit(drag->get_sprite_id(), drop->get_unit_id())))
                swap_xp_bars(gui, drag, drop, user);
            if (check_same_unit(drag->get_sprite_id(), drop->get_unit_id()))
                increase_exp(gui, drag, drop, user);
            else if (!(drag->get_display()))
                return (0);
        }
        else
            swap_xp_bars(gui, drag, drop, user);
        drop->remove_sprite();
        if (drop->get_display())
            drop->generate_static_sprite(drag->get_sprite_id(), 2, file);
        swap = drag->get_sprite_id();
        drag->set_sprite_id(drop->get_unit_id());
        drop->set_unit_id(swap);
        if (drag->get_display())
            user->set_unit(drag->get_gui_id() - 5, drag->get_sprite_id());
        user->set_unit(drop->get_gui_id() - 5, drop->get_unit_id());
    }
    write_changes(user);
    return (drop->get_unit_id());
}

static int  check_price(int unit_id)
{
    if (unit_id >= 1 && unit_id <= 40)
        return (1);
    else if (unit_id >= 41 && unit_id <= 70)
        return (2);
    else if (unit_id >= 71 && unit_id <= 100)
        return (3);
    else if (unit_id >= 101 && unit_id <= 120)
        return (4);
    return (0); 
}

static bool check_afford(int unit_id, int user_gold)
{
    if (unit_id >= 1 && unit_id <= 40 && user_gold >= 1)
        return (true);
    else if (unit_id >= 41 && unit_id <= 70 && user_gold >= 2)
        return (true);
    else if (unit_id >= 71 && unit_id <= 100 && user_gold >= 3)
        return (true);
    else if (unit_id >= 101 && unit_id <= 120 && user_gold >= 4)
        return (true);
    return (false);
}

static void drag_drop_controls(std::multimap <gui_type, gui_base *> *gui, \
    gui_drag_drop *drag, Vector2 mouse_point, default_run *user)
{
    mINI::INIFile file ("data/draft_gui.ini");
    //picked up
    if (drag && CheckCollisionPointRec(mouse_point, drag->get_bounds()) && \
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && drag->get_unit_id())
    {
        drag->remove_sprite();
        drag->generate_picked_up_sprite(drag->get_sprite_id(), 2, file);
        drag->set_is_picked_up(true);
    }
    //dropped
    if (drag && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && \
        drag->get_is_picked_up())
    {
        int overlapped = check_collision(mouse_point, gui, drag->get_gui_id());

        if (!(check_afford(drag->get_sprite_id(), user->get_gold())) && \
            !(drag->get_display()))
            overlapped = -1;
        if (overlapped > -1)
        {
            if (!(drag->get_display()))
            {
                user->deduct_gold(check_price(handle_drop(gui, drag, \
                    overlapped, user)));
                user->set_store(drag->get_gui_id(), drag->get_unit_id());
            }
            else
                handle_drop(gui, drag, overlapped, user);
        }
        //sold
        if (drag->get_display() && CheckCollisionPointRec(mouse_point, \
            find_gui_by_id(gui, 9, G_HITBOX)->get_bounds()))
        {
            user->add_gold(check_price(drag->get_sprite_id()));
            user->set_unit(drag->get_gui_id() - 5, 0);
            user->set_unit_exp(drag->get_gui_id() - 5, 0);
            user->set_unit_max_exp(drag->get_gui_id() - 5, 2);
            drag->set_sprite_id(0);
        }
        drag->set_is_picked_up(false);
        drag->set_unit_id(drag->get_sprite_id());
        drag->remove_sprite();
        if (drag->get_display() && drag->get_unit_id())
            drag->generate_static_sprite(drag->get_unit_id(), 2, file);
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

void    draw_drag_drops(gui_base *gui, game_settings settings)
{
    gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> (gui);

    if (drag_drop && drag_drop->get_is_picked_up())
        drag_drop->draw_sprite(settings.mouse_point, settings.sprite_size, \
        true);
    else if (drag_drop && drag_drop->get_display() && \
        drag_drop->get_sprite_id())
        drag_drop->draw_sprite((Vector2) { 0, 0 }, settings.sprite_size, \
        false);
}

void    check_drag_drops(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point, default_run *user)
{
    auto range = gui->equal_range(G_DRAG_DROP);
    static int  timer = 0;

    timer++;
    for (auto i = range.first; i != range.second; ++i)
    {
        gui_drag_drop   *drag = dynamic_cast <gui_drag_drop *> (i->second);

        if (drag && (drag->get_unit_id() || drag->get_sprite_id()))
            drag_drop_controls(gui, drag, mouse_point, user);
        if (drag && timer % 20 == 0)
        {
            drag->increment_state();
            timer = 0;
        }
    }
}