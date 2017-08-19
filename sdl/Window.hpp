#ifndef TETRIS_CPP_SDL2_WINDOW_HPP
#define TETRIS_CPP_SDL2_WINDOW_HPP

#include <SDL.h>
#include <string>
#include "Surface.hpp"

namespace SDL {

    class Window {
        SDL_Window *sdl_window;
        Surface *screen_surface;

    public:
        Window(std::string name = "SDL Window", int width = 600, int height = 400);

        Surface *getSurface();

        void renderToScreen();

        virtual ~Window();
    };

}

#endif //TETRIS_CPP_SDL2_WINDOW_HPP
