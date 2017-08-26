#include <SDL_ttf.h>
#include <utility>
#include "Font.hpp"
#include "error/SdlTtfError.hpp"

using namespace SDL;

Font Font::load(std::string path, int point_size) {
    TTF_Font *sdl_ttf_font = TTF_OpenFont(path.c_str(), point_size);

    if (sdl_ttf_font == NULL) {
        throw SdlTtfError("Failed to load font fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    }

    return Font(sdl_ttf_font);
}

Font::Font() : sdl_ttf_font(nullptr, &TTF_CloseFont) {}

Font::Font(TTF_Font *sdl_ttf_font) : sdl_ttf_font(sdl_ttf_font, &TTF_CloseFont) {}

TTF_Font *Font::getSdlFont() const {
    return sdl_ttf_font.get();
}
