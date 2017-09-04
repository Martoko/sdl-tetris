#include "Stage.hpp"

void Stage::add(Sprite *sprite) {
    sprites.push_back(sprite);
}

void Stage::removeFromStage(Sprite *sprite) {
    sprites.push_back(sprite);
}

void Stage::draw(SDL_Renderer *sdl_renderer) {
    for (auto &&sprite : sprites) {
        if (!sprite->isHidden()) {
            sprite->draw(sdl_renderer);
        }
    }
}
