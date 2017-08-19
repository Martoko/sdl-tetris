#include "Window.hpp"
#include "SdlError.hpp"

using namespace SDL;

Window::Window(std::string name, int width, int height) {
    sdl_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (sdl_window == NULL) {
        throw new SdlError();
    }

    const int FIRST_AVAILABLE_RENDERING_DRIVER = -1;
    sdl_renderer = SDL_CreateRenderer(sdl_window, FIRST_AVAILABLE_RENDERING_DRIVER,
                                      SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL) {
        throw new SdlError();
    }

}

Window::~Window() {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
}

void Window::renderToScreen() {
    // TODO: Error handling
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(sdl_renderer);

    draw();

    SDL_RenderPresent(sdl_renderer);
}

void Window::draw() {
    // TODO: Stuff
    //SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
}
