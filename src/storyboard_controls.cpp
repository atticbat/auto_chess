#include "storyboard_controls.hpp"

# define RAYGUI_IMPLEMENTATION
# include "../raylib-cpp/include/raygui.h"

void    set_boundaries(std::multimap <gui_type, gui_base *> *gui, \
    int off_x, int off_y, mINI::INIFile file, float scale)
{
    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
    {
        i->second->set_bounds(off_x, off_y, (int)i->first, file, scale);
        i->second->set_text_size(i->second->get_text_size() * scale);
    }
}

void    draw_gui(std::multimap <gui_type, gui_base *> *gui, Vector2 \
    screen_dim, Vector2 set_dim, Vector2 mouse_point)
{
    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
    {
        switch (i->first)
        {
            case (G_LABEL):
            case (G_DYNAMIC_LABEL):
            {
                DrawText(i->second->get_text(), i->second->get_bounds().x, \
                    i->second->get_bounds().y, i->second->get_text_size(), \
                    BLACK);
            } break ;
            case (G_CHECKBOX):
            {
                set_checkbox(i->second, GuiCheckBox(i->second->get_bounds(), \
                    i->second->get_text(), check_checkbox(i->second)));
            } break ;
            case (G_BUTTON):
            {
                set_button(i->second, GuiButton(i->second->get_bounds(), \
                    i->second->get_text()));
            } break ;
            case (G_SLIDER):
            {
                set_slider(i->second, GuiSliderBar(i->second->get_bounds(), \
                    NULL, NULL, check_slider_value(i->second), \
                    check_slider_min(i->second), check_slider_max(i->second)));
            } break ;
            case (G_SCROLLBAR):
            {
                GuiScrollPanel(i->second->get_bounds(), NULL, \
                    check_scrollbar_content(i->second), \
                    get_scrollbar_scroll(i->second));
            } break ;
            case (G_DROPDOWN):
            {
                int resolution_x = parse_resolution(check_dropdown_choice(\
                    i->second));

                GuiDropdownBox(i->second->get_bounds(), i->second->get_text(),\
                    get_dropdown_choice_ptr(i->second), \
                    check_dropdown_edit_mode(i->second));
                set_dropdown_default(i->second, resolution_x, (resolution_x / \
                    16) * 9);
            } break ;
            case (G_TEXTBOX):
            {
                draw_textbox(i->second);
            } break ;
            case (G_DRAG_DROP):
            {
                gui_drag_drop   *drag_drop = dynamic_cast <gui_drag_drop *> \
                    (i->second);

                GuiDrawRectangle(drag_drop->get_bounds(), 1, BLACK, RAYWHITE);
                if (drag_drop && drag_drop->get_is_picked_up())
                    drag_drop->draw_sprite(mouse_point);
                else if (drag_drop->get_display() && drag_drop->get_sprite_id())
                    drag_drop->draw_sprite((Vector2) {0, 0});
            } break ;
            case (G_PROGRESS_BAR):
            {
                //to do
                ;
            } break ;
            default: break ;
        }
    }
}

gui_base    *find_gui_by_id(std::multimap <gui_type, gui_base*> *gui, \
    int id, gui_type state)
{
    auto    range = gui->equal_range(state);

    for (auto i = range.first; i != range.second; ++i)
    {
        if (i->second->get_id() == id)
            return (i->second);
    }
    return (NULL);
}

void    del_gui(std::multimap <gui_type, gui_base *> *gui)
{
    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
        delete (i->second);
    gui->clear(); 
}

game_state  check_gui(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point, game_state current_state)
{
    current_state = check_buttons(gui, current_state);
    check_dropdowns(gui, mouse_point);
    check_textboxes(gui, mouse_point);
    check_drag_drops(gui, mouse_point);
    return (current_state);
}