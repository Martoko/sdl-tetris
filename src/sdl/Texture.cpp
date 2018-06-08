#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.hpp"
#include "error/SdlTtfError.hpp"
#include "error/SdlImgError.hpp"
#include "error/SdlError.hpp"

using namespace SDL;

Texture Texture::load(const SDL::Renderer *renderer, std::string path) {
    SDL_Texture *sdl_texture = nullptr;

    // Load image at specified path
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == nullptr) {
        throw SdlImgError("Unable to load image " + path);
    }

    // Create texture from surface pixels
    sdl_texture = SDL_CreateTextureFromSurface(renderer->get(), loaded_surface);
    if (sdl_texture == nullptr) {
        throw SdlError("Unable to create texture from surface from " + path);
    }

    // Get image dimensions
    int width = loaded_surface->w;
    int height = loaded_surface->h;

    // Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);

    return Texture(sdl_texture, width, height);
}

// TODO: Maybe move to renderer
Texture Texture::fromText(const Renderer &renderer, const Font &font,
                          std::string text,
                          SDL_Color color) {
    // Render text surface
    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(font.get(), text.c_str(), color);
    if (text_surface == nullptr) {
        throw SdlTtfError("Unable to render text surface!");
    }

    // Create texture from surface pixels
    SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(renderer.get(), text_surface);
    if (sdl_texture == nullptr) {
        throw SdlError("Unable to create texture from rendered text!");
    }

    // Get image dimensions
    int width = text_surface->w;
    int height = text_surface->h;

    // Get rid of old surface
    SDL_FreeSurface(text_surface);

    return Texture(sdl_texture, width, height);
}

Texture::Texture(SDL_Texture *sdl_texture, int width, int height) :
        width(width), height(height), sdl_texture(sdl_texture, &SDL_DestroyTexture) {}

SDL_Texture *Texture::get() const {
    return sdl_texture.get();
}
