#include "sprite.hpp"

void button_status_check(sprite *btn, Vector2 mousePoint)
{
    btn->trigger = false;
    if (CheckCollisionPointRec(mousePoint, btn->hitbox))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btn->state = 2;
        else
            btn->state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btn->trigger = true;
    }
    else
        btn->state = 0;
    btn->source.x = btn->state * btn->width;
}

void    unload_sprite(sprite **btn, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        UnloadTexture(btn[0][i].image);
        // btn[0][i].destroy();
        i++;
    }
    free (*btn);
    *btn = NULL;
}