#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Sdl.hpp"
#include "error/SdlError.hpp"
#include "error/SdlImgError.hpp"
#include "error/SdlTtfError.hpp"

using namespace SDL;

Sdl::Sdl() {
    initSdl();

    setTextureFilteringToLinear();

    initSdlImage();

    initSdlTtf();
}

void Sdl::initSdl() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw SdlError("SDL could not initialize!");
    }
}

void Sdl::initSdlImage() {
    int imgFlags = IMG_INIT_PNG;
    const int FAILURE = 0;
    if ((IMG_Init(imgFlags) & imgFlags) == FAILURE) {
        throw SdlImgError("SDL_image could not initialize!");
    }
}

void Sdl::initSdlTtf() const {
    int result = TTF_Init();
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw SdlTtfError("SDL_ttf could not initialize!");
    }
}

void Sdl::setTextureFilteringToLinear() {
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) {
        printf("Warning: Linear tetromino_texture filtering not enabled!");
    }
}

Sdl::~Sdl() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
