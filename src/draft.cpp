#include "draft.hpp"

void    initialise_draft (std::multimap <gui_type, gui_base *> *gui, \
    default_run *user)
{
    mINI::INIFile    file ("data/draft_gui.ini");
    int             label_defaults[9] = {12, 1, 80, 20, 0, 0, 0, 0, 0};
    int             available_units[5] = { 1, 3, 4, 5, 32 };

    for (int i = 0; i < 9; i++)
    {
        gui_dynamic_label   *label = new gui_dynamic_label;

        label->set_text(i, 1, 32, file);
        if (i == 0)
            label->update_text(user->get_gold(), false);
        else if (i < 2 || i > 5)
            label->update_text(label_defaults[i], false);
        else
            label->update_text(label_defaults[i], true);
        label->set_id(i);
        gui->insert(std::pair<gui_type, gui_dynamic_label *> \
            (G_DYNAMIC_LABEL, label));
    }
    for (int i = 9; i < 14; i++)
    {
        gui_button  *button = new gui_button;
        button->set_text(i - 9, 3, 24, file);
        button->set_destination(parse_destination(i - 9, file));
        gui->insert(std::pair<gui_type, gui_button *> (G_BUTTON, button));
    }

    for (int i = 14; i < 19; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;
        drag_drop->set_unit_id(user->get_store_slot(i - 14));
        drag_drop->set_text(i - 14, 8, 24, file);
        drag_drop->set_id(i);
        gui->insert(std::pair<gui_type, gui_drag_drop *> (G_DRAG_DROP, drag_drop));
    }
    for (int i = 19; i < 27; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;
        drag_drop->set_unit_id(user->get_roster_slot(i - 19));
        if (drag_drop->get_unit_id())
            drag_drop->generate_static_sprite (drag_drop->get_unit_id(), 2, file);
        drag_drop->set_text(i - 14, 8, 24, file);
        drag_drop->set_id(i);
        drag_drop->set_display(true);
        gui->insert(std::pair<gui_type, gui_drag_drop *> (G_DRAG_DROP, drag_drop));
    }
    // {
    //     gui_progress_bar    *bar = new gui_progress_bar(0, 0, 8);
    //     bar->set_text(0, 9, 16, file);
    //     bar->set_id(27);
    //     gui->insert(std::pair<gui_type, gui_base *> (G_PROGRESS_BAR, bar));
    // }
}

void    reroll_shop(std::multimap <gui_type, gui_base *> *gui, default_run \
    *user)
{
    mINI::INIFile   file ("data/draft_gui.ini");
   int              available_units[5] = { 1, 3, 4, 5, 32 };
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
