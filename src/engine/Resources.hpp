#ifndef TETRIS_CPP_SDL2_RESOURCES_HPP
#define TETRIS_CPP_SDL2_RESOURCES_HPP

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

    void loadImagesIn(const SDL::Window &window, std::string directory);

    SDL::Texture *getTexture(std::string name);

    void clear();
}

#endif //TETRIS_CPP_SDL2_RESOURCES_HPP
