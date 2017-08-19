#ifndef TETRIS_CPP_SDL2_TEXTURE_HPP
#define TETRIS_CPP_SDL2_TEXTURE_HPP

#include <string>
#include <SDL.h>

namespace SDL {

    class Texture {

    public:
        static Texture *fromPath(SDL_Renderer *sdl_renderer, std::string path);

        Texture(SDL_Texture *sdl_texture);

        virtual ~Texture();

        SDL_Texture *sdl_texture;
    };

}

#endif //TETRIS_CPP_SDL2_TEXTURE_HPP
