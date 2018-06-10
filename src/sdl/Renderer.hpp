#pragma once

#include <SDL_render.h>
#include <memory>
#include "Texture.hpp"
#include "Font.hpp"
#include "Window.hpp"

namespace SDL {

    typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> SdlRendererPointer;

    class Renderer final {
        SdlRendererPointer sdl_renderer;

    public:
        explicit Renderer(Window &window);

        void present();

        void copy(SDL::Texture &texture, SDL_Rect &src_rect, SDL_Rect &dst_rect) const;

        Texture createText(const Font &font, std::string text,
                           SDL_Color color = SDL_Color{0, 0, 0}) const;

        Texture load(std::string path) const;

        SDL_Renderer *get() const;

    private:
        void clear();

        static SDL_Renderer *createSdlRenderer(const Window &window);
    };

}