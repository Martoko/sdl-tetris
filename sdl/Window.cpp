#include "Window.hpp"
#include "SdlError.hpp"

using namespace SDL;

Window::Window(std::string name, int width, int height) {
    sdl_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (sdl_window == NULL) {
        throw new SdlError();
    }

    SDL_Surface *sdl_surface = SDL_GetWindowSurface(sdl_window);

    if (sdl_surface == NULL) {
        throw new SdlError();
    }

    screen_surface = new Surface(sdl_surface);
}

Window::~Window() {
    delete screen_surface;
    SDL_DestroyWindow(sdl_window);
}

Surface *Window::getSurface() {
    return screen_surface;
}

void Window::renderToScreen() {
    int result = SDL_UpdateWindowSurface(sdl_window);
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw new SdlError();
    }
}
