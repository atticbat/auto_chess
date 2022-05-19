#include "settings.hpp"

const char  *settings_paths[2] = {"resources/return.png", "resources/settings.png"};

sprite  *initialise_settings(int *unique_id, int offset, int screen_width, int screen_height)
{
    sprite  *btn;
    int     i;
    int     offset_x;
    int     offset_y;

    i = 0;
    offset_x = ((screen_width - 960) / 2) + offset;
    offset_y = ((screen_height + 540) / 2) - offset - 40;
    btn = (sprite *) malloc (sizeof(sprite) * SETTINGS_BUTTONS);
    while (i < SETTINGS_BUTTONS)
    {
        btn[i].initialise(*unique_id, (char *) settings_paths[i], 3, offset_x + i * 128, offset_y);
        *unique_id = *unique_id + 1;
        i++;
    }
    return (btn);
}

void    draw_settings(sprite *btn, int screen_width, int screen_height)
{
    int i;
    int offset_left;
    int offset_top;

    i = 0;
    // offset_left = ((screen_width - 960) / 2); 
    // offset_top = ((screen_height - 540) / 2);
    // DrawRectangle(offset_left, offset_top, 960, 540, RAYWHITE);
    while (i < SETTINGS_BUTTONS)
    {
        DrawTextureRec(btn[i].image, btn[i].source, (Vector2){ btn[i].hitbox.x, btn[i].hitbox.y }, WHITE);
        i++;
    }
}

game_state  check_settings(sprite *btn, Vector2 mousePoint)
{
    int i;

    i = 0;
    while (i < SETTINGS_BUTTONS)
    {
        button_status_check(&btn[i], mousePoint);
        i++;
    }
    if (btn[0].trigger == true)
        return (MENU);
    else if (btn[1].trigger == true)
        return (SETTINGS);
    else
        return (SETTINGS);
}
