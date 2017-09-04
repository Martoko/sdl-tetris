#include "Window.hpp"
#include "error/SdlError.hpp"

using namespace SDL;

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

SDL_Renderer *Window::createSdlRendererFromSdlWindow(SDL_Window *sdl_window) {
    const int FIRST_AVAILABLE_RENDERING_DRIVER = -1;
    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window,
                                                    FIRST_AVAILABLE_RENDERING_DRIVER,
                                                    SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL) {
        throw SdlError();

    }

    return sdl_renderer;
}

Window::Window(std::string name, int width, int height) :
        sdl_window(createSdlWindow(name, width, height), &SDL_DestroyWindow),
        renderer(createSdlRendererFromSdlWindow(sdl_window.get())) {}

void Window::renderToScreen() {
    renderer.present();
}

const Renderer &Window::getRenderer() const {
    return renderer;
}

