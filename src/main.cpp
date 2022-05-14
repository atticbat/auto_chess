#include "auto_chess.hpp"
// #include <stdio.h>

const char  *db_names[13] = {"ID", "Cost", "Tag 1", "Tag 2", "Tag 3", "Attack", "Health", "Atk Spd", "Abl Pwr", "Defense", "Range", "Abl Cost", "Abl Gauge"};

static void button_status_check(sprite *btn, Vector2 mousePoint)
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
            if ((key >= 48) && (key <= 57) && (in->count < MAX_INPUT_CHARS))
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
    // DrawText(TextFormat("INPUT CHARS: %i/%i", in->count, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
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

int main(void)
{
    const int   screen_width = 1600;
    const int   screen_height = 900;
    game_state  current_state = LOADING;
    int         frame_count = 0;
    sprite      btn_new;
    sprite      btn_sett;
    sprite      btn_data;
    sprite      btn_return;
    sprite      btn_edit;
    input_box   in_db[13];
    int         i = 0;
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    InitWindow(screen_width, screen_height, "auto_chess");
    btn_new.initialise("resources/new_game.png", 3, 64, 64);
    btn_sett.initialise("resources/settings.png", 3, 64, 128);
    btn_data.initialise("resources/database.png", 3, 64, 196);
    btn_return.initialise("resources/return.png", 3, screen_width - 184, screen_height - 104);
    btn_edit.initialise("resources/edit_item.png", 3, ((13 * 256) % (screen_width - 64)) + 64, 64 * ((13 * 256) / (screen_width - 64)) + 64);
    while (i < 13)
    {
        in_db[i].initialise(((i * 256) % (screen_width - 64)) + 64, 64 * ((i * 256) / (screen_width - 64)) + 64);
        i++;
    }
    // initialise_all_inputs_db(&in_db);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();

        switch(current_state)
        {
            case LOADING:
            {
                frame_count++;
                if (frame_count > 120)
                    current_state = MENU;
            } break;
            case MENU:
            {
                button_status_check(&btn_new, mousePoint);
                button_status_check(&btn_sett, mousePoint);
                button_status_check(&btn_data, mousePoint);
                if (btn_new.trigger == true)
                    current_state = DRAFT;
                else if (btn_sett.trigger == true)
                    current_state = SETTINGS;
                else if (btn_data.trigger == true)
                    current_state = DATABASE;
            } break;
            case SETTINGS:
            {
                button_status_check(&btn_return, mousePoint);
                if (btn_return.trigger == true)
                    current_state = MENU;
            } break;
            case DRAFT:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = SIMULATION;
            } break;
            case SIMULATION:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    current_state = MENU;
            } break;
            case DATABASE:
            {
                bool    no_hover = true;
                i = 0;
                while (i < 13)
                {
                    input_status_check(&in_db[i], mousePoint, &frame_count);
                    i++;
                    if (in_db[i].on_text == true)
                        no_hover = false;
                }
                if  (no_hover)
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                button_status_check(&btn_return, mousePoint);
                button_status_check(&btn_edit, mousePoint);
                if (btn_return.trigger == true)
                    current_state = MENU;
                if (btn_edit.trigger == true)
                    ;
                //at start of 
            }
            default: break;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (current_state)
            {
                case LOADING:
                {
                    DrawText("LOADING...", 20, 20, 40, LIGHTGRAY);
                    DrawText("PLEASE WAIT.", 290, 220, 20, GRAY);
                } break;
                case MENU:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, SKYBLUE);
                    DrawTextureRec(btn_new.image, btn_new.source, (Vector2){ btn_new.hitbox.x, btn_new.hitbox.y }, WHITE);
                    DrawTextureRec(btn_sett.image, btn_sett.source, (Vector2){ btn_sett.hitbox.x, btn_sett.hitbox.y }, WHITE);
                    DrawTextureRec(btn_data.image, btn_data.source, (Vector2){ btn_data.hitbox.x, btn_data.hitbox.y }, WHITE);
                    DrawText("MENU", 200, 64, 20, DARKBLUE);
                    DrawText("CHOOSE AN OPTION to CONTINUE", 200, 96, 20, DARKBLUE);
                } break;
                case SETTINGS:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, LIGHTGRAY);
                    DrawTextureRec(btn_return.image, btn_return.source, (Vector2){ btn_return.hitbox.x, btn_return.hitbox.y }, WHITE);
                    DrawText("SETTINGS", 120, 160, 20, DARKGRAY);
                    DrawText("PRESS RETURN to JUMP to MENU SCREEN", 120, 220, 20, DARKGRAY);
                } break;
                case DRAFT:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, YELLOW);
                    DrawText("DRAFT", 120, 160, 20, DARKBROWN);
                    DrawText("PRESS ENTER or TAP to JUMP to SIMULATION SCREEN", 120, 220, 20, DARKBROWN);
                } break;
                case SIMULATION:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, PINK);
                    DrawText("SIMULATION", 120, 160, 20, DARKPURPLE);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, DARKPURPLE);
                } break;
                case DATABASE:
                {
                    DrawRectangle(0, 0, screen_width, screen_height, LIME);
                    i = 0;
                    while (i < 13)
                    {
                        DrawText(db_names[i], in_db[i].box.x, in_db[i].box.y - 20, 20, DARKGREEN);
                        input_status_visual(&in_db[i], frame_count);
                        i++;
                    }
                    DrawTextureRec(btn_return.image, btn_return.source, (Vector2){ btn_return.hitbox.x, btn_return.hitbox.y }, WHITE);
                    DrawTextureRec(btn_edit.image, btn_edit.source, (Vector2){ btn_edit.hitbox.x, btn_edit.hitbox.y }, WHITE);
                    DrawText("DATABASE", screen_width - 184, screen_height - 48, 20, DARKGREEN);
                } break;
                default: break;
            }
        EndDrawing();
    }
    UnloadTexture(btn_new.image);
    UnloadTexture(btn_sett.image);
    UnloadTexture(btn_data.image);
    UnloadTexture(btn_return.image);
    UnloadTexture(btn_edit.image);
    CloseWindow();
    return (0);
}