#include <SDL_image.h>
#include "App.hpp"
#include "SdlError.hpp"
#include "SdlImgError.hpp"

using namespace SDL;

App::App() {
    srand((unsigned int) time(0));

    initSdl();

    setTextureFilteringToLinear();

    initSdlImage();
}

void App::initSdl() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw new SdlError("SDL could not initialize!");
    }
}

void App::initSdlImage() {
    int imgFlags = IMG_INIT_PNG;
    const int FAILURE = 0;
    if (IMG_Init(imgFlags) & imgFlags == FAILURE) {
        throw new SdlImgError("SDL_image could not initialize!");
    }
}

void App::setTextureFilteringToLinear() {
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) {
        printf("Warning: Linear texture filtering not enabled!");
    }
}

App::~App() {
    IMG_Quit();
    SDL_Quit();
}
