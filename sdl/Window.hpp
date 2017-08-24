#ifndef TETRIS_CPP_SDL2_WINDOW_HPP
#define TETRIS_CPP_SDL2_WINDOW_HPP

#include <SDL.h>
#include <string>
#include "Surface.hpp"

namespace SDL {

    class Window {
    protected:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        void clearScreen();

    public:
        Window(std::string name = "SDL Window", int width = 600, int height = 400);

        void renderToScreen();

        virtual ~Window();
    };

}

#endif //TETRIS_CPP_SDL2_WINDOW_HPP
