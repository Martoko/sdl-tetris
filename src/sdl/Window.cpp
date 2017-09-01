#include "Window.hpp"
#include "error/SdlError.hpp"

using namespace SDL;

Window::Window(std::string name, int width, int height) {
    SDL_Window *sdl_window = SDL_CreateWindow(name.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              width, height,
                                              SDL_WINDOW_SHOWN);
    if (sdl_window == NULL) {
        throw SdlError();
    }

    this->sdl_window.reset(sdl_window);

    const int FIRST_AVAILABLE_RENDERING_DRIVER = -1;
    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window,
                                                    FIRST_AVAILABLE_RENDERING_DRIVER,
                                                    SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL) {
        throw SdlError();
    }

    this->sdl_renderer.reset(sdl_renderer);
}

void Window::renderToScreen() {
    // First we present to the screen
    SDL_RenderPresent(sdl_renderer.get());

    // Then we clear the internal drawing, in preparation for the next draw call
    clearScreen();
}

void Window::clearScreen() {
    int result = SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    if (result == -1) {
        throw SdlError();
    }

    result = SDL_RenderClear(sdl_renderer.get());
    if (result == -1) {
        throw SdlError();
    }
}

