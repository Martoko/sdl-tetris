#pragma once

#include <string>
#include "../sdl/Texture.hpp"
#include "../sdl/Font.hpp"
#include "../sdl/Window.hpp"

namespace Resources {
    struct FontNameAndSize {
        std::string name;
        int size;

        bool operator<(const Resources::FontNameAndSize &other) const {
            return this->name < other.name || (this->name == other.name && this->size < other.size);
        }
    };

    void loadImage(const SDL::Window &window, std::string filename);

    SDL::Texture &getTexture(std::string name);

    void clear();
}