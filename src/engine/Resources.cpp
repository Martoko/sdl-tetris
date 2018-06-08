#include <vector>
#include <map>
#include "Resources.hpp"

namespace Resources {
    namespace {
        std::map<std::string, SDL::Texture> textures;
        std::map<FontNameAndSize, SDL::Font> fonts;
    }

    void loadImage(const SDL::Window &window, std::string filename) {
        auto texture = textures.find(filename);

        if (texture != textures.end()) {
            throw std::runtime_error("Trying to load image twice resources/images/" + filename);
        }

        textures.insert(std::map<std::string, SDL::Texture>::value_type(
                filename,
                SDL::Texture::load(&window.getRenderer(), "resources/images/" + filename)
        ));
    }

    SDL::Texture &getTexture(std::string name) {
        auto found = textures.find(name);

        if (found == textures.end()) {
            throw std::runtime_error("Trying to get texture, that has not been loaded "
                                     "resources/images/" + name);
        }

        return found->second;
    }

    void clear() {
        textures.clear();
        fonts.clear();
    }
}