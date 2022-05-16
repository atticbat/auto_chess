#include "menu.hpp"

const char  *menu_paths[5] = {"resources/new_game.png", "resources/load.png", "resources/settings.png", "resources/exit.png", "resources/database.png"};

sprite  *initialise_menu(int *unique_id, int offset)
{
    sprite  *btn;
    int i;

    i = 0;
    btn = (sprite *) malloc (sizeof(sprite) * MENU_BUTTONS);
    while (i < MENU_BUTTONS)
    {
        btn[i].initialise(*unique_id, (char *) menu_paths[i], 3, offset, offset * i + offset);
        *unique_id = *unique_id + 1;
        i++;
    }
    return (btn);
}

void    draw_menu(sprite *btn, int screen_width, int screen_height)
{
    int i;

    i = 0;
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screen_width, screen_height, SKYBLUE);
    while (i < MENU_BUTTONS)
    {
        DrawTextureRec(btn[i].image, btn[i].source, (Vector2){ btn[i].hitbox.x, btn[i].hitbox.y }, WHITE);
        i++;
    }
    DrawText("MENU", 200, 64, 20, DARKBLUE);
    DrawText("CHOOSE AN OPTION to CONTINUE", 200, 96, 20, DARKBLUE);
}

game_state  check_menu(sprite *btn, Vector2 mousePoint)
{
    int i;

    i = 0;
    while (i < MENU_BUTTONS)
    {
        button_status_check(&btn[i], mousePoint);
        i++;
    }
    if (btn[0].trigger == true)
        return (DRAFT);
    else if (btn[2].trigger == true)
        return (SETTINGS);
    else if (btn[4].trigger == true)
        return (DATABASE);
    else
        return (MENU);
}

void    unload_menu(sprite *btn)
{
    int i;

    i = 0;
    while (i < MENU_BUTTONS)
    {
        UnloadTexture(btn[i].image);
        i++;
    }
}