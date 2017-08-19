#ifndef TETRIS_CPP_SDL2_SURFACE_HPP
#define TETRIS_CPP_SDL2_SURFACE_HPP

namespace SDL {

    class Surface {
        SDL_Surface *sdl_surface;

    public:
        Surface(SDL_Surface *sdl_surface);

        virtual ~Surface();

        void clear();
    };

}

#endif //TETRIS_CPP_SDL2_SURFACE_HPP
