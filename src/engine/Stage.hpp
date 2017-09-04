#ifndef TETRIS_CPP_SDL2_STAGE_HPP
#define TETRIS_CPP_SDL2_STAGE_HPP


#include <vector>
#include "Sprite.hpp"

class Stage {
    std::vector<Sprite *> sprites;

public:
    void add(Sprite *sprite);

    void removeFromStage(Sprite *sprite);

    void draw(SDL_Renderer *sdl_renderer);
};


#endif //TETRIS_CPP_SDL2_STAGE_HPP
