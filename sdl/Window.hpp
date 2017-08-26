#ifndef TETRIS_CPP_SDL2_WINDOW_HPP
#define TETRIS_CPP_SDL2_WINDOW_HPP

#include <SDL.h>
#include <string>
#include <memory>

typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> WindowPointer;
typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> RendererPointer;

namespace SDL {

    class Window {
    protected:
        WindowPointer sdl_window = WindowPointer(nullptr, &SDL_DestroyWindow);
        RendererPointer sdl_renderer = RendererPointer(nullptr, &SDL_DestroyRenderer);

        void clearScreen();

    public:
        Window(std::string name = "SDL Window", int width = 600, int height = 400);

        void renderToScreen();
    };

}

#endif //TETRIS_CPP_SDL2_WINDOW_HPP
