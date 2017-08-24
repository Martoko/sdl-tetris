#include <SDL_surface.h>
#include "Surface.hpp"
#include "SdlError.hpp"

using namespace SDL;

Surface::Surface(SDL_Surface *sdl_surface) : sdl_surface(sdl_surface) {}

Surface::~Surface() {
    SDL_FreeSurface(sdl_surface);
}

void Surface::clear() {
    int result = SDL_FillRect(sdl_surface, NULL, SDL_MapRGB(sdl_surface->format, 0xFF, 0xFF, 0xFF));
    const int SUCCESS = 0;

    if (result != SUCCESS) {
        throw SdlError("");
    }
}
