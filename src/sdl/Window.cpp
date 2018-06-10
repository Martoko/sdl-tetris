#include "Window.hpp"
#include "error/SdlError.hpp"

using namespace SDL;

Window::Window(std::string name, int width, int height) :
        sdl_window(createSdlWindow(name, width, height), &SDL_DestroyWindow) {}

SDL_Window *Window::createSdlWindow(std::string name, int width, int height) {
    SDL_Window *sdl_window = SDL_CreateWindow(name.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              width, height,
                                              SDL_WINDOW_SHOWN);
    if (sdl_window == NULL) {
        throw SdlError();
    }

    return sdl_window;
}

SDL_Window *Window::get() const {
    return sdl_window.get();
}

