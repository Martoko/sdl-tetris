#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.hpp"
#include "SdlTtfError.hpp"
#include "SdlImgError.hpp"
#include "SdlError.hpp"

using namespace SDL;

Texture *Texture::fromPath(SDL_Renderer *sdl_renderer, std::string path) {
    SDL_Texture *sdl_texture = NULL;

    // Load image at specified path
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL) {
        throw SdlImgError("Unable to load image " + path);
    }

    // Create texture from surface pixels
    sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, loaded_surface);
    if (sdl_texture == NULL) {
        throw SdlError("Unable to create texture from " + path);
    }

    // Get image dimensions
    int width = loaded_surface->w;
    int height = loaded_surface->h;

    // Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);

    return new Texture(sdl_texture, width, height);
}

Texture *Texture::fromText(SDL_Renderer *sdl_renderer, TTF_Font *font, std::string text,
                           SDL_Color color) {
    // Render text surface
    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (text_surface == NULL) {
        throw SdlTtfError("Unable to render text surface!");
    }

    // Create texture from surface pixels
    SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
    if (sdl_texture == NULL) {
        throw SdlError("Unable to create texture from rendered text!");
    }

    // Get image dimensions
    int width = text_surface->w;
    int height = text_surface->h;

    // Get rid of old surface
    SDL_FreeSurface(text_surface);

    return new Texture(sdl_texture, width, height);
}

Texture::Texture(SDL_Texture *sdl_texture, int width, int height) :
        width(width), height(height), sdl_texture(sdl_texture) {}

Texture::~Texture() {
    SDL_DestroyTexture(sdl_texture);
}
