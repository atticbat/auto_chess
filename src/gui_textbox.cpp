#include "gui_textbox.hpp"

static void input_status_visual(gui_textbox *textbox)
{
    Rectangle   bounds = textbox->get_bounds();

    DrawRectangleRec(bounds, LIGHTGRAY);
    if (textbox->get_edit_mode())
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, \
            BLACK);
    else
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, \
            DARKGRAY);
    DrawText(textbox->get_text(), bounds.x + 4, bounds.y + 8, 24, BLACK);
    if (textbox->get_edit_mode())
    {
        DrawText("_", (int) bounds.x + 8 + MeasureText(textbox->get_text(), \
            24), (int) bounds.y + 8, 24, BLACK);
    }
}

void    input_status_check(gui_textbox *textbox, Vector2 mousePoint)
{
    if (CheckCollisionPointRec(mousePoint, textbox->get_bounds()))
        textbox->set_edit_mode(true);
    else
        textbox->set_edit_mode(false);
    if (textbox->get_edit_mode())
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 48) && (key <= 57))
                textbox->add_letter(key);
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE))
            textbox->delete_letter();
    }
}

void    check_textboxes(std::multimap <gui_type, gui_base *> *gui, \
    Vector2 mouse_point)
{
    bool no_hover = true;
    auto range = gui->equal_range(G_TEXTBOX);

    for (auto i = range.first; i != range.second; ++i)
    {
        gui_textbox *textbox = dynamic_cast<gui_textbox *> (i->second);

        input_status_check(textbox, mouse_point);
        if (textbox->get_edit_mode())
            no_hover = false;
    }
    if  (no_hover)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void    draw_textbox(gui_base *gui)
{
    gui_textbox *textbox = dynamic_cast <gui_textbox *> (gui);

    input_status_visual(textbox);
}