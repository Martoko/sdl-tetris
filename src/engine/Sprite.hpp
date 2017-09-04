#ifndef TETRIS_CPP_SDL2_SPRITE_HPP
#define TETRIS_CPP_SDL2_SPRITE_HPP


#include "../sdl/Texture.hpp"

class Sprite {
    int x, y = 0;
    bool hidden = false;

public:
    virtual void draw(SDL_Renderer *sdl_renderer) = 0;

    bool isHidden() const;

    void setHidden(bool hidden);
};


#endif //TETRIS_CPP_SDL2_SPRITE_HPP
