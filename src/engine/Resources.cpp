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

    void loadFont(std::string filename, int point_size) {
        auto font = fonts.find({filename, point_size});

        if (font != fonts.end()) {
            throw std::runtime_error("Trying to load font twice resources/images/" + filename);
        }

        fonts.insert(std::map<FontNameAndSize, SDL::Font>::value_type(
                {filename, point_size},
                SDL::Font::load("resources/fonts/" + filename, point_size)
        ));
    }

    void loadImagesIn(const SDL::Window &window, std::string directory) {
        throw std::runtime_error("Not implemented");
    }

    SDL::Texture *getTexture(std::string name) {
        auto found = textures.find(name);

        if (found == textures.end()) {
            throw std::runtime_error("Trying to get texture, that has not been preloaded "
                                             "resources/images/" + name);
        }

        return &found->second;
    }

    SDL::Font *getFont(std::string name, int point_size) {
        auto found = fonts.find({name, point_size});

        if (found == fonts.end()) {
            throw std::runtime_error("Trying to get font, that has not been preloaded "
                                             "resources/fonts/" + name);
        }

        return &found->second;
    }

    void clear() {
        textures.clear();
        fonts.clear();
    }
}