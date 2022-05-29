#include "draft.hpp"

void    initialise_draft (std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile       file ("data/draft_gui.ini");
    int label_defaults[9] = {12, 1, 80, 20, 0, 0, 0, 0, 0};

    for (int i = 0; i < 9; i++)
    {
        gui_dynamic_label   *label = new gui_dynamic_label;

        label->set_text(i, 1, 32, file);
        if (i < 2 || i > 5)
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
        drag_drop->set_unit_id(1);
        drag_drop->set_text(i - 14, 8, 24, file);
        drag_drop->set_id(i);
        gui->insert(std::pair<gui_type, gui_drag_drop *> (G_DRAG_DROP, drag_drop));
    }
    for (int i = 19; i < 27; i++)
    {
        gui_drag_drop   *drag_drop = new gui_drag_drop;
        drag_drop->set_unit_id(0);
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