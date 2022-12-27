#include "database.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int     ft_atoi(const char *str);

void    set_database_boundaries(std::multimap <gui_type, gui_base *> *gui, Vector2 screen_dim)
{
    mINI::INIFile   file("data/database_gui.ini");
    const float header_offset = 64 * (((DATABASE_INPUTS) * 160) / (screen_dim.x - 160)) + 96;
    int index;

    index = 0;
    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
    {
        if (i->first == G_LABEL)
        {
            int divided = ((index * 160) % ((int) screen_dim.x - 160)) + 64;
            int remainder = 64 * ((index * 160) / ((int) screen_dim.x - 160)) + 32;
            i->second->set_bounds(divided, remainder, (int)i->first, file, 1);
            index++;
        }
        else if (i->first == G_BUTTON)
        {
            int divided = ((index * 160) % ((int) screen_dim.x - 160)) + 64;
            int remainder = 64 * ((index * 160) / ((int) screen_dim.x - 160)) + 32;
            i->second->set_bounds(divided, remainder, (int)i->first, file, 1);
            index++;
        }
        else if (i->first == G_SCROLLBAR)
        {
            set_scrollbar_bounds(i->second, 0, header_offset, (float) screen_dim.x, \
                screen_dim.y - header_offset);
            set_scrollbar_content(i->second, 0, header_offset, 1080, 2880);
        }
        else if (i->first == G_TEXTBOX)
        {
            int divided = (((index - 15) * 160) % ((int) screen_dim.x - 160)) + 64;
            int remainder = 64 * (((index - 15) * 160) / ((int) screen_dim.x - 160)) + 32;
            i->second->set_bounds(divided, remainder, (int)i->first, file, 1);
            index++;
        }
    }
}

void    initialise_database(std::multimap <gui_type, gui_base *> *gui)
{
    mINI::INIFile   file ("data/database_gui.ini");

    // initialise_unit_db();
    for (int i = 0; i < 13; i++)
    {
        gui_base    *label = new gui_base;

        label->set_text(i, 0, 20, file);;
        label->unique_id = i;
        gui->insert(std::pair<gui_type, gui_base *> (G_LABEL, label));
    }

    for (int i = 13; i < 15; i++)
    {
        gui_button    *button = new gui_button;

        button->set_text(i - 13, 3, 24, file);
        button->unique_id = i;
        button->destination = parse_destination(i - 13, file);
        gui->insert(std::pair<gui_type, gui_base *> (G_BUTTON, button));
    }
    {
        gui_scrollbar   *scrollbar =  new gui_scrollbar;
        scrollbar->unique_id = 15;
        gui->insert(std::pair<gui_type, gui_base *> (G_SCROLLBAR, scrollbar));
    }
    for (int i = 16; i < 29; i++)
    {
        gui_textbox *textbox = new gui_textbox;
        
        textbox->set_text(i - 16, 24);;
        textbox->unique_id = i;
        gui->insert(std::pair<gui_type, gui_base *> (G_TEXTBOX, textbox));
    }
}

static bool check_not_empty(std::multimap <gui_type, gui_base*> *gui)
{
    for (std::multimap <gui_type, gui_base *>::iterator i = gui->begin(); \
        i != gui->end(); ++i)
    {
        if (i->first == G_TEXTBOX)
        {
            gui_textbox *textbox = dynamic_cast<gui_textbox *> (i->second);

            if (textbox)
            {
                if (textbox->text[0] == '\0')
                    return (0);
            }
        }
    }
    return (1);
}

static void write_unit_db(std::multimap <gui_type, gui_base*> *gui, \
    char **unit_db)
{
    FILE *read_txt;
    int id = 0;
    int i;

    {
        gui_textbox  *textbox = dynamic_cast <gui_textbox *> \
            (find_gui_by_id(gui, 16, G_TEXTBOX));
        if (textbox)
            id = atoi(textbox->text);
    }
    read_txt = fopen("arrays/unit_database.txt", "w+");
    i = 0;
    while (i < id)
    {
        fprintf(read_txt, "%s", unit_db[i]);
        i++;
    }
    int j = 0;
    while (j < DATABASE_INPUTS)
    {
        fprintf(read_txt, "%s", find_gui_by_id(gui, 16 + j, \
            G_TEXTBOX)->text);
        if (j < 12)
            fprintf(read_txt, "%s", ",");
        j++;
        if (j == DATABASE_INPUTS)
            fprintf(read_txt, "%s", "\n");
    }
    i++;
    while (i < MAX_UNITS)
    {
        fprintf(read_txt, "%s", unit_db[i]);
        i++;
    }
    fclose(read_txt);
}

void    edit_unit(std::multimap <gui_type, gui_base*> *gui, char **unit_db)
{
    if (check_not_empty(gui))
        write_unit_db(gui, unit_db);
}

void    draw_grid(int scroll_h_offset, int scroll_v_offset, char **unit_db)
{
    int i;
    int j;
    int k;
    int l;
    mINI::INIFile file ("data/UnitNames.ini");
    mINI::INIStructure ini;
    file.read(ini);
    char    int_str[4];
    char    int_str2[4];

    i = 0;
    while (i < MAX_UNITS)
    {
        j = 0;
        k = 0;
        l = 0;
        ft_itoa(i, int_str);
        DrawText(ini.get("UnitNames").get(int_str).c_str(), 32 + 112 * j + \
            scroll_h_offset, 192 + i * 20 + scroll_v_offset, 16, BLACK);
        while (j < 13)
        {
            if (unit_db[i][k] == ',' || unit_db[i][k] == '\0')
            {
                l = 0;
                ft_itoa(j, int_str2);
                DrawText(ini.get("DatabaseColumns").get(int_str2).c_str(), \
                    256 + 112 * j + scroll_h_offset, 192 + i * 20 + \
                    scroll_v_offset, 16, BLACK);
                j++;
            }
            else if (unit_db[i][k] >= '0' && unit_db[i][k] <= '9')
            {
                DrawTextCodepoint(GetFontDefault(), unit_db[i][k], (Vector2) \
                    { (float)(328 + 112 * j + 9 * l + scroll_h_offset), \
                    (float)(192 + i * 20) + scroll_v_offset }, 16, BLACK);
                l++;
            }
            k++;
        }
        i++;
    }
}

char    **initialise_unit_db(void)
{
	int		fd;
	char	**db;

    db = (char **) malloc ((128) * sizeof(char *));
	fd = open("arrays/unit_database.txt", O_RDONLY);
	for (int i = 0; i < 128; i++)
		db[i] = get_next_line(fd);
	close (fd);
    return (db);
}

char    **del_db(char **unit_db)
{
    if (unit_db)
    {
        for (int i = 0; i < 128; i++)
        {
            free (unit_db[i]);
        }
        free (unit_db); 
    }
    return (NULL);
}