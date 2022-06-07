#include "draft.hpp"

static gui_dynamic_label    *generate_dlabel(default_run *user, int i)
{
    gui_dynamic_label   *label = new gui_dynamic_label;
    int                 label_defaults[9] = {12, 1, 80, 20, 0, 0, 0, 0, 0};
    mINI::INIFile    file ("data/draft_gui.ini");

    label->set_text(i, 1, 32, file);
    if (i == 0)
        label->update_text(user->get_gold(), false); 
    else if ((i < 2 || i > 5) && i < 9)
        label->update_text(label_defaults[i], false);
    else if (i >= 2 && i <= 5)
        label->update_text(label_defaults[i], true);
    label->set_id(i);
    return (label);
}

void    initialise_draft (std::multimap <gui_type, gui_base *> *gui, \
    default_run *user)
{
    mINI::INIFile    file ("data/draft_gui.ini");

    for (int i = 0; i < 9; i++)
        gui->insert(std::pair<gui_type, gui_dynamic_label *> \
            (G_DYNAMIC_LABEL, generate_dlabel(user, i)));
    gui->insert(std::pair<gui_type, gui_dynamic_label *> (G_HITBOX, \
        generate_dlabel(user, 9)));
    for (int i = 10; i < 15; i++)
        gui->insert(std::pair<gui_type, gui_button *> (G_BUTTON, \
            generate_button(i - 10, file)));
    for (int i = 15; i < 20; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;

        drag_drop->set_unit_id(user->get_store_slot(i - 15));
        drag_drop->set_text(i - 15, 8, 24, file);
        drag_drop->set_id(i);
        gui->insert(std::pair<gui_type, gui_drag_drop *> (G_DRAG_DROP, drag_drop));
    }
    for (int i = 20; i < 28; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;

        drag_drop->set_unit_id(user->get_roster_slot(i - 20));
        drag_drop->set_text(i - 15, 8, 24, file);
        drag_drop->set_id(i);
        if (drag_drop->get_unit_id())
            drag_drop->generate_static_sprite (drag_drop->get_unit_id(), 2, file);
        drag_drop->set_display(true);
        gui->insert(std::pair<gui_type, gui_drag_drop *> (G_DRAG_DROP, drag_drop));
    }
    for (int i = 28; i < 37; i++)
    {
        gui_progress_bar    *bar;
        if (i < 36)
            bar = new gui_progress_bar(user->get_unit_xp(i - 28), 0, \
                user->get_unit_max_xp(i - 28));
        else
            bar = new gui_progress_bar(user->get_exp(), 0, user->get_exp_cap());
        bar->set_text(i - 28, 9, 16, file);
        bar->set_id(i);
        gui->insert(std::pair<gui_type, gui_base *> (G_PROGRESS_BAR, bar));
    }

}

void    reroll_shop(std::multimap <gui_type, gui_base *> *gui, default_run \
    *user)
{
    mINI::INIFile   file ("data/draft_gui.ini");
   int              available_units[5] = { 1, 3, 4, 5, 42 };
    auto            range = gui->equal_range(G_DRAG_DROP);

    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->first == G_DRAG_DROP)
        {
            gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> \
                (i->second);

            if (drag_drop && !(drag_drop->get_display()))
            {
                drag_drop->set_unit_id(available_units[rand() % 5]);
                user->set_store(drag_drop->get_gui_id(), \
                    drag_drop->get_unit_id());
            }
        }
    }
}
