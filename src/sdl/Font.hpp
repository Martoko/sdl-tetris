#ifndef TETRIS_CPP_SDL2_FONT_HPP
#define TETRIS_CPP_SDL2_FONT_HPP

#include <string>
#include <memory>

namespace SDL {

    class Font {
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> sdl_ttf_font;

    public:
        static Font load(std::string path, int point_size);

        Font();

        Font(TTF_Font *sdl_ttf_font);

        TTF_Font *getSdlFont() const;
    };

}

#endif //TETRIS_CPP_SDL2_FONT_HPP
