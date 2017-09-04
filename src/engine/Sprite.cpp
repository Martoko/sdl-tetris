#include "Sprite.hpp"

bool Sprite::isHidden() const {
    return hidden;
}

void Sprite::setHidden(bool hidden) {
    Sprite::hidden = hidden;
}
