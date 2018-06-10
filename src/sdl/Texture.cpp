#include "Texture.hpp"

using namespace SDL;

Texture::Texture(SDL_Texture *sdl_texture, int width, int height) :
        width(width), height(height), sdl_texture(sdl_texture, &SDL_DestroyTexture) {}

SDL_Texture *Texture::get() const {
    return sdl_texture.get();
}
