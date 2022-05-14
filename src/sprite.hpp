#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "auto_chess.hpp"

class sprite
{
    public:
        Texture2D   image;
        float       width;
        Rectangle   source;
        Rectangle   hitbox;
        int         state;
        bool        trigger;
        void        initialise(char *address, int frames, float off_x, float off_y)
        {
            image = LoadTexture(address);
            width = (float) image.width / frames;
            source = { 0, 0, width, (float) image.height };
            hitbox = { off_x, off_y, width, (float) image.height };
            state = 0;
            trigger = false;
        }
};

#endif