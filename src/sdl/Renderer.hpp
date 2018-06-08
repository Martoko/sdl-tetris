#pragma once

#include <SDL_render.h>
#include <memory>
#include "Texture.hpp"

namespace SDL {

    class Texture;

    typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> SdlRendererPointer;

    class Renderer final {
        SdlRendererPointer sdl_renderer;

    public:
        Renderer(SDL_Renderer *sdl_renderer);

        void present();

        SDL_Renderer *get() const;

        void copy(SDL::Texture &texture, SDL_Rect &src_rect, SDL_Rect &dst_rect) const;

    private:
        void clear();
    };

}