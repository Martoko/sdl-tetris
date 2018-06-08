#pragma once

#include "../sdl/Renderer.hpp"

class Object {
public:
    int x = 0;
    int y = 0;

    virtual void draw(SDL::Renderer &sdl_renderer) = 0;
};