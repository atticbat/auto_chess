#include "database.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_next_line.hpp"
#include <iostream>
#include <fstream>

int         atoi(const char *str);
const char  *db_names[13] = {"ID", "Cost", "Tag 1", "Tag 2", "Tag 3", "Attack", "Health", "AtkSpd", "AblPwr", "Defense", "Range", "AblCost", "Gauge"};
const char  *db_paths[2] = {"resources/edit_item.png", "resources/return.png"};
char        unit_db[MAX_UNITS][52];
const int   db_max_input[13] = {3, 1, 2, 2, 2, 4, 5, 4, 4, 4, 1, 4, 4};

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

sprite  *initialise_db(int *unique_id, int offset, int screen_width, int screen_height)
{
    sprite  *btn;
    int     i;
    int     divided;
    int     remainder;

    i = 0;
    btn = (sprite *) malloc (sizeof(sprite) * DATABASE_BUTTONS);
    while (i < DATABASE_BUTTONS)
    {
        divided = ((DATABASE_INPUTS + i) * 160) % (screen_width - 160) + 64;
        remainder = 64 * (((DATABASE_INPUTS + i) * 160) / (screen_width - 160)) + 32;
        btn[i].initialise(*unique_id, (char *) db_paths[i], 3, divided, remainder);
        *unique_id = *unique_id + 1;
        i++;
    }
    initialise_unit_db();
    return (btn);
}

static void input_status_check(input_box *in, Vector2 mousePoint, int *frame_count)
{
    if (CheckCollisionPointRec(mousePoint, in->box))
        in->on_text = true;
    else
        in->on_text = false;
    if (in->on_text)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 48) && (key <= 57) && (in->check_if_max()))
            {
                (in->input)[in->count] = (char)key;
                (in->input)[in->count + 1] = '\0';
                (in->count)++;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (in->count)--;
            if (in->count < 0)
                in->count = 0;
            (in->input)[in->count] = '\0';
        }
    }
    if (in->on_text)
        (*frame_count)++;
    else
        *frame_count = 0;
}

static void input_status_visual(input_box *in, int frame_count)
{
    DrawRectangleRec(in->box, LIGHTGRAY);
    if (in->on_text)
        DrawRectangleLines((int)(in->box).x, (int)(in->box).y, (int)(in->box).width, (int)(in->box).height, RED);
    else
        DrawRectangleLines((int)(in->box).x, (int)(in->box).y, (int)(in->box).width, (int)(in->box).height, DARKGRAY);
    DrawText(in->input, (int)(in->box).x + 5, (int) (in->box).y + 8, 32, MAROON);
    if (in->on_text)
    {
        if (in->count < MAX_INPUT_CHARS)
        {
            if (((frame_count/60)%2) == 0)
                DrawText("_", (int) (in->box).x + 8 + MeasureText(in->input, 32), (int)(in->box).y + 12, 32, MAROON);
            else
                DrawText ("Press BACKSPACE to delete chars...", 230, 300, 20, DARKGREEN);
        }
    }
}

static void write_unit_db(input_box *in_db)
{
    FILE *read_txt;
    int id;
    int i;

    id = atoi(in_db[0].input);
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
        fprintf(read_txt, in_db[j].input);
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

game_state  check_database(sprite *btn, input_box *in_db, Vector2 mousePoint, int *frame_count)
{
    bool    no_hover;
    int     i;

    no_hover = true;
    i = 0;
    while (i < 13)
    {
        input_status_check(&in_db[i], mousePoint, frame_count);
        i++;
        if (in_db[i].on_text == true)
            no_hover = false;
    }
    if  (no_hover)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    i = 0;
    while (i < DATABASE_BUTTONS)
    {
        button_status_check(&btn[i], mousePoint);
        i++;
    }
    if (btn[0].trigger == true)
    {
        write_unit_db(in_db);
        initialise_unit_db();
    }
    if (btn[1].trigger == true)
        return (MENU);
    return (DATABASE);
}

void    draw_grid(int scroll_offset)
{
    int i;
    int j;
    int k;
    int l;

    i = 0;
    while (i < MAX_UNITS)
    {
        j = 0;
        k = 0;
        l = 0;
        while (j < 13)
        {
            if (unit_db[i][k] == ',' || unit_db[i][k] == '\0')
            {
                l = 0;
                DrawText(db_names[j], 64 + 112 * j, 192 + i * 20 + scroll_offset, 16, BLACK);
                j++;
            }
            else if (unit_db[i][k] >= '0' && unit_db[i][k] <= '9')
            {
                DrawTextCodepoint(GetFontDefault(), unit_db[i][k], (Vector2) { (float)(128 + 112 * j + 9 * l), (float)(192 + i * 20) + scroll_offset }, 16, BLACK);
                l++;
            }
            k++;
        }
        i++;
    }
}

void    draw_database(sprite *btn, input_box *in_db, int screen_width, int screen_height, int frame_count)
{
    int i;

    i = 0;
    DrawRectangle(0, 0, screen_width, 64 * (((DATABASE_INPUTS + i) * 160) / (screen_width - 160)) + 96, LIME);
    while (i < 13)
    {
        DrawText(db_names[i], in_db[i].box.x, in_db[i].box.y - 20, 20, DARKGREEN);
        input_status_visual(&in_db[i], frame_count);
        i++;
    }
    i = 0;
    while (i < DATABASE_BUTTONS)
    {
        DrawTextureRec(btn[i].image, btn[i].source, (Vector2){ btn[i].hitbox.x, btn[i].hitbox.y }, WHITE);
        i++;
    }
}

input_box   *initialise_db_in(int screen_width)
{
    input_box   *in_db;
    int         i;
    int         divided;
    int         remainder;

    in_db = (input_box *) malloc (sizeof(input_box) * DATABASE_INPUTS);
    i = 0;
    while (i < DATABASE_INPUTS)
    {
        divided = ((i * 160) % (screen_width - 160)) + 64;
        remainder = 64 * ((i * 160) / (screen_width - 160)) + 32;
        in_db[i].initialise(divided, remainder, db_max_input[i]);
        i++;
    }
    return (in_db);
}
