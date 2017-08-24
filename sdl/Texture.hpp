#ifndef TETRIS_CPP_SDL2_TEXTURE_HPP
#define TETRIS_CPP_SDL2_TEXTURE_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace SDL {

    class Texture {
    public:
        int width, height;

        static Texture *fromPath(SDL_Renderer *sdl_renderer, std::string path);

        static Texture *fromText(SDL_Renderer *sdl_renderer, TTF_Font *font, std::string text,
                                 SDL_Color color = SDL_Color {0, 0, 0});

        Texture(SDL_Texture *sdl_texture);

        Texture(SDL_Texture *sdl_texture, int width, int height);

        virtual ~Texture();

        SDL_Texture *sdl_texture;
    };

}

#endif //TETRIS_CPP_SDL2_TEXTURE_HPP
