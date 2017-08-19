#include "App.hpp"
#include "SdlError.hpp"

using namespace SDL;

App::App() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw new SdlError("SDL could not initialize!");
    }
}

App::~App() {
    SDL_Quit();
}
