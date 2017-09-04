#ifndef TETRIS_CPP_SDL2_TEXTURE_HPP
#define TETRIS_CPP_SDL2_TEXTURE_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include "Renderer.hpp"
#include "Font.hpp"

namespace SDL {

    class Renderer;

    class Texture {
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> sdl_texture;
    public:
        int width, height;

        static Texture load(const SDL::Renderer *renderer, std::string path);

        static Texture fromText(
                const Renderer &renderer, const Font &font, std::string text,
                SDL_Color color = SDL_Color {0, 0, 0});

        Texture(SDL_Texture *sdl_texture, int width, int height);

        SDL_Texture *get() const;
    };

}

#endif //TETRIS_CPP_SDL2_TEXTURE_HPP
