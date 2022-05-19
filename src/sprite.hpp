#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "../raylib-cpp/include/raylib-cpp.hpp"
# include "../config.hpp"

typedef enum    game_state{LOADING = 0, MENU, SETTINGS, DRAFT, SIMULATION, DATABASE} game_state;

class sprite
{
    private:
        int         unique_id;
        int         sprite_id;
    public:
        Texture2D   image;
        float       width;
        Rectangle   source;
        Rectangle   hitbox;
        int         state;
        bool        trigger;
        void        initialise(int id1, char *address, int frames, float off_x, float off_y)
        {
            static int  id2 = 0;

            unique_id = id1;
            sprite_id = id2;
            id2++;
            image = LoadTexture(address);
            width = (float) image.width / frames;
            source = { 0, 0, width, (float) image.height };
            hitbox = { off_x, off_y, width, (float) image.height };
            state = 0;
            trigger = false;
        }
        int         get_unique_id (void) { return (unique_id); }
        int         get_sprite_id (void) { return (sprite_id); }
};

void    button_status_check(sprite *btn, Vector2 mousePoint);
void    unload_sprite(sprite **btn, int count);

#endif