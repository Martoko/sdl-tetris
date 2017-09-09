#ifndef TETRIS_CPP_SDL2_OBJECT_HPP
#define TETRIS_CPP_SDL2_OBJECT_HPP

#include "../sdl/Renderer.hpp"

class Object {
public:
    int x, y = 0;

    virtual void draw(SDL::Renderer *sdl_renderer) = 0;
};


#endif //TETRIS_CPP_SDL2_OBJECT_HPP
