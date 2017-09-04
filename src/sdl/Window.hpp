#ifndef TETRIS_CPP_SDL2_WINDOW_HPP
#define TETRIS_CPP_SDL2_WINDOW_HPP

#include <SDL.h>
#include <string>
#include <memory>
#include "Renderer.hpp"

namespace SDL {

    typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> SdlWindowPointer;

    class Window {
    protected:
        SdlWindowPointer sdl_window;
        SDL::Renderer renderer;

    public:
        Window(std::string name = "SDL Window", int width = 600, int height = 400);

        void renderToScreen();

        const Renderer &getRenderer() const;


    private:
        static SDL_Window *createSdlWindow(std::string name, int width, int height);

        static SDL_Renderer *createSdlRendererFromSdlWindow(SDL_Window *sdl_window);
    };

}

#endif //TETRIS_CPP_SDL2_WINDOW_HPP
