#include "simulation.hpp"

void    initialise_simulation(std::multimap <gui_type, gui_base *> *gui, \
    default_run *user)
{
    mINI::INIFile file ("data/simulation_gui.ini");
    mINI::INIStructure ini;

    file.read(ini);
}

game_state  simulation(int *x_offset)
{
    if (IsKeyPressed(KEY_LEFT) && *x_offset < 0)
        *x_offset += 16;
    else if (IsKeyDown(KEY_LEFT) && *x_offset < 0)
        *x_offset += 8;
    if (IsKeyPressed(KEY_RIGHT) && *x_offset > -5248)
        *x_offset -= 16;
    else if (IsKeyDown(KEY_RIGHT) && *x_offset > -5248)
        *x_offset -= 8;
    return (SIMULATION);
}

void    draw_simulation(int x_offset)
{
    for (int i = 0; i < 56; i++)
    {
        DrawText(TextFormat("%i", i), 128 * i + x_offset + 4, 404, 24, BLACK);
        DrawRectangleLines(128 * i + x_offset, 400, 128, 256, BLACK);
    }
}