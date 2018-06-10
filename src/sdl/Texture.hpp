#pragma once

#include <SDL.h>
#include <memory>

namespace SDL {

    class Texture {
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> sdl_texture;
    public:
        int width, height;

        Texture(SDL_Texture *sdl_texture, int width, int height);

        SDL_Texture *get() const;
    };

}