#pragma once

#include <string>
#include <memory>
#include <SDL_ttf.h>

namespace SDL {

    class Font final {
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> sdl_ttf_font;

    public:
        static Font load(std::string path, int point_size);

        Font(TTF_Font *sdl_ttf_font);

        TTF_Font *get() const;
    };

}