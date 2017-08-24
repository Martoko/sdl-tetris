#include <SDL_image.h>
#include "Texture.hpp"

using namespace SDL;

// TODO: Redo this function
Texture *Texture::fromPath(SDL_Renderer *sdl_renderer, std::string path) {
    //The final tetromino_texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create tetromino_texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(sdl_renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create tetromino_texture from %s! SDL Error: %s\n", path.c_str(),
                   SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return new Texture(newTexture);
}

Texture::Texture(SDL_Texture *sdl_texture) : sdl_texture(sdl_texture) {}

Texture::~Texture() {
    SDL_DestroyTexture(sdl_texture);
}
