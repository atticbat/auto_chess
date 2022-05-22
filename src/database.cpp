#include "database.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int         atoi(const char *str);
char        unit_db[MAX_UNITS][52];

static void initialise_unit_db(void)
{
    int i;
    int len;

    std::ifstream input("arrays/unit_database.txt");
    std::string line;
    i = 0;
    while (std::getline(input, line))
    {
        len = strlen(line.c_str());
        memcpy(unit_db[i], (char *) line.c_str(), len);
        unit_db[i][len + 1] = '\0';
        i++;
    }
}

void    set_database_boundaries(gui_base **settings_gui, int screen_width, int screen_height)
{
    mINI::INIFile   file("data/database_gui.ini");
    const char  *bound_modes[3] = {"LabelBounds", "TextboxBounds", "ButtonBounds"};
    const float header_offset = 64 * (((DATABASE_INPUTS) * 160) / (screen_width - 160)) + 96;

    for (int i = 0; i < 13; i++)
    {
        int divided = ((i * 160) % (screen_width - 160)) + 64;
        int remainder = 64 * ((i * 160) / (screen_width - 160)) + 32;
        settings_gui[i]->set_bounds(divided, remainder, i, bound_modes[0], file);
        settings_gui[i + 13]->set_bounds(divided, remainder, i, bound_modes[1], file);
    }
    for (int i = 26; i < 28; i++)
    {
        int divided = (((i - 13) * 160) % (screen_width - 160)) + 64;
        int remainder = 64 * (((i - 13) * 160) / (screen_width - 160)) + 32;
        settings_gui[i]->set_bounds(divided, remainder, i - 26, bound_modes[2], file);
    }
    {
        gui_scrollbar   *scrollbar = dynamic_cast <gui_scrollbar *> (settings_gui[28]);
        scrollbar->set_bounds(0, header_offset, (float) screen_width, screen_height - header_offset);
        scrollbar->set_content(0, header_offset, 1080, 2880);
    }
}

gui_base    **initialise_database(void)
{
    gui_base        **database_gui;
    gui_base        **ptr;
    mINI::INIFile   file ("data/database_gui.ini");
    const char      *text_modes[2] = {"LabelText", "ButtonText"};
    const int       db_max_input[13] = {3, 1, 2, 2, 2, 4, 5, 4, 4, 4, 1, 4, 4};

    initialise_unit_db();
    database_gui = (gui_base **) malloc (sizeof(gui_base *) * 29);
    ptr = database_gui;
    for (int i = 0; i < 13; i++)
    {
        gui_base    *label = new gui_base;
        label->set_text(i, text_modes[0], file);;
        *ptr = label;
        ptr++;
    }
    for (int i = 13; i < 26; i++)
    {
        gui_textbox    *textbox = new gui_textbox;
        textbox->set_max_input(db_max_input[i - 13]);
        *ptr = textbox;
        ptr++;
    }
    for (int i = 26; i < 28; i++)
    {
        gui_button    *button = new gui_button;
        button->set_text(i - 26, text_modes[1], file);
        *ptr = button;
        ptr++;
    }
    {
        gui_scrollbar   *scrollbar =  new gui_scrollbar;
        *ptr = scrollbar;
    }
    return(database_gui);
}

static void write_unit_db(gui_base **db_gui)
{
    FILE *read_txt;
    int id = 0;
    int i;

    {
        gui_textbox  *textbox = dynamic_cast <gui_textbox *> (db_gui[13]);
        if (textbox)
            id = atoi(textbox->get_text());
    }
    read_txt = fopen("arrays/unit_database.txt", "w+");
    i = 0;
    while (i < id)
    {
        fprintf(read_txt, unit_db[i]);
        fprintf(read_txt, "\n");
        i++;
    }
    int j = 0;
    while (j < DATABASE_INPUTS)
    {
        fprintf(read_txt, db_gui[j + 13]->get_text());
        if (j < 12)
            fprintf(read_txt, ",");
        j++;
        if (j == DATABASE_INPUTS)
            fprintf(read_txt, "\n");
    }
    i++;
    while (i < MAX_UNITS)
    {
        fprintf(read_txt, unit_db[i]);
        fprintf(read_txt, "\n");
        i++;
    }
    fclose(read_txt);
}

static void input_status_check(gui_textbox *textbox, Vector2 mousePoint, int *frame_count)
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
    if (textbox->get_edit_mode())
        (*frame_count)++;
    else
        *frame_count = 0;
}

static void input_status_visual(gui_textbox *textbox, int frame_count)
{
    Rectangle   bounds = textbox->get_bounds();
    DrawRectangleRec(textbox->get_bounds(), LIGHTGRAY);
    if (textbox->get_edit_mode())
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, BLACK);
    else
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, DARKGRAY);
    DrawText(textbox->get_text(), bounds.x + 4, bounds.y + 8, 24, BLACK);
    if (textbox->get_edit_mode())
    {
        if (((frame_count/60)%2) == 0)
            DrawText("_", (int) bounds.x + 8 + MeasureText(textbox->get_text(), 24), (int) bounds.y + 8, 24, BLACK);
    }
}

static bool check_not_empty(gui_base **db_gui)
{
    for (int i = 13; i < 26; i++)
    {
        gui_textbox *textbox = dynamic_cast<gui_textbox *> (db_gui[i]);
        if (textbox)
        {
            if (textbox->get_text()[0] == '\0')
                return (0);
        }
    }
    return (1);
}

game_state  check_database(gui_base **db_gui, Vector2 mousePoint, int *frame_count)
{
    bool    no_hover;

    no_hover = true;
    for (int i = 13; i < 26; i++)
    {
        gui_textbox *textbox = dynamic_cast<gui_textbox *> (db_gui[i]);
        input_status_check(textbox, mousePoint, frame_count);
        if (textbox->get_edit_mode())
            no_hover = false;
    }
    if  (no_hover)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (check_button_press(db_gui[26]))
    {
        if (check_not_empty(db_gui))
        {
            write_unit_db(db_gui);
            initialise_unit_db();
        }
    }
    if (check_button_press(db_gui[27]))
        return (MENU);
    return (DATABASE);
}

void    draw_grid(int scroll_h_offset, int scroll_v_offset)
{
    int i;
    int j;
    int k;
    int l;
    mINI::INIFile file ("data/UnitNames.ini");
    const char  *db_names[13] = {"ID", "Cost", "Tag 1", "Tag 2", "Tag 3", "Attack", "Health", "AtkSpd", "AblPwr", "Defense", "Range", "AblCost", "Gauge"};
    mINI::INIStructure ini;
    file.read(ini);
    char    int_str[4];

    i = 0;
    while (i < MAX_UNITS)
    {
        j = 0;
        k = 0;
        l = 0;
        ft_itoa(i, int_str);
        DrawText(ini.get("UnitNames").get(int_str).c_str(), 32 + 112 * j + scroll_h_offset, 192 + i * 20 + scroll_v_offset, 16, BLACK);       
        while (j < 13)
        {
            if (unit_db[i][k] == ',' || unit_db[i][k] == '\0')
            {
                l = 0;
                DrawText(db_names[j], 192 + 112 * j + scroll_h_offset, 192 + i * 20 + scroll_v_offset, 16, BLACK);
                j++;
            }
            else if (unit_db[i][k] >= '0' && unit_db[i][k] <= '9')
            {
                DrawTextCodepoint(GetFontDefault(), unit_db[i][k], (Vector2) { (float)(256 + 112 * j + 9 * l + scroll_h_offset), (float)(192 + i * 20) + scroll_v_offset }, 16, BLACK);
                l++;
            }
            k++;
        }
        i++;
    }
}

void    draw_database(gui_base **db_gui, int screen_width, int screen_height, int frame_count)
{
    const char  *db_names[13] = {"ID", "Cost", "Tag 1", "Tag 2", "Tag 3", "Attack", "Health", "AtkSpd", "AblPwr", "Defense", "Range", "AblCost", "Gauge"};

    {
        gui_scrollbar   *scrollbar = dynamic_cast <gui_scrollbar *> (db_gui[28]);
        if (scrollbar)
        {
            GuiScrollPanel(scrollbar->get_bounds(), NULL, scrollbar->get_content(), &(scrollbar->scroll));
            draw_grid(scrollbar->scroll.x, scrollbar->scroll.y);
        }
    }
    DrawRectangle(0, 0, screen_width, 64 * (((DATABASE_INPUTS) * 160) / (screen_width - 160)) + 96, LIME);
    for (int i = 13; i < 26; i++)
    {
        gui_textbox *textbox = dynamic_cast <gui_textbox *> (db_gui[i]);
        DrawText(db_names[i - 13], textbox->get_bounds().x, textbox->get_bounds().y - 20, 20, DARKGREEN);
        input_status_visual(textbox, frame_count);
    }
    for (int i = 26; i < 28; i++)
    {
        gui_button  *button = dynamic_cast<gui_button *> (db_gui[i]);
        if (button)
            button->set_checked(GuiButton(button->get_bounds(), button->get_text())); 
    }
}
