#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "../raylib-cpp/include/raylib-cpp.hpp"
# include "../config.hpp"
# include "conversion_functions.hpp"
# include "game_progression.hpp"

class sprite_base
{
protected:
    const char  *modes[4] = { "SpriteAddresses1x", "SpriteAddresses2x", "SpriteAddresses3x", "SpriteAddresses4x"}; 
    float       width;
    int         unit_id;
    // Rectangle   bounds;
    Texture2D   image;
    Rectangle   source;
    int         state = 0;
public:
    sprite_base(int id, int frames, int mode)
    {
        mINI::INIFile file ("data/draft_gui.ini");
        mINI::INIStructure ini;
        char    c[5];
        file.read(ini);
        ft_itoa(id, c);
        unit_id = id;
        image = LoadTexture(ini.get(modes[mode]).get(c).c_str());
        if (frames <= 0)
            frames = 1;
        width = (float) image.width / frames;
        source = { 0, 0, width, (float) image.height };
    }
    ~sprite_base()
    {
        UnloadTexture(image);
    }
    // void    set_bounds(Vector2 location)
    // {
    //     bounds = (Rectangle) { location.x, location.y, width, \
    //         (float) image.height };
    // }
    void    set_state(int _state)
    {
        state = _state;
        source = { width * state, 0, width, (float) image.height };
    }
    void        set_unit_id(int id) { unit_id = id; }
    int         get_unit_id (void) { return (unit_id); }
    // Rectangle   get_bounds(void) { return (bounds); }
    Rectangle   get_source(void) { return (source); }
    Texture2D   get_image(void) { return (image); }
    float       get_width(void) { return (width); }
};

class sprite_picked_up : public sprite_base
{
public:
    sprite_picked_up(int id, int frames, int mode) : sprite_base(id, frames, mode) { ; }
    ~sprite_picked_up()
    {
        UnloadTexture(image);
    }
    Vector2     get_offset_location(Vector2 mouse_point)
    {
        return (Vector2 { mouse_point.x - width / 2, mouse_point.y - \
            image.height * 9 / 10 });
    }
};

#endif