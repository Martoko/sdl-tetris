#pragma once

#include <SDL.h>
#include <string>
#include <memory>

namespace SDL {

    typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> SdlWindowPointer;

    class Window final {
        SdlWindowPointer sdl_window;

    public:
        explicit Window(std::string name = "SDL Window", int width = 600, int height = 400);

        SDL_Window *get() const;

    private:
        static SDL_Window *createSdlWindow(std::string name, int width, int height);
    };

}