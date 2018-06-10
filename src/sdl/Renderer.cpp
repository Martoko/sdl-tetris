#include <SDL_image.h>
#include "Renderer.hpp"
#include "error/SdlError.hpp"
#include "error/SdlTtfError.hpp"
#include "error/SdlImgError.hpp"

using namespace SDL;

Renderer::Renderer(Window &window) : sdl_renderer(createSdlRenderer(window), &SDL_DestroyRenderer) {}

SDL_Renderer *Renderer::createSdlRenderer(const Window &window) {
    const int FIRST_AVAILABLE_RENDERING_DRIVER = -1;
    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(window.get(),
                                                    FIRST_AVAILABLE_RENDERING_DRIVER,
                                                    SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL) {
        throw SdlError();
    }

    return sdl_renderer;
}

void Renderer::clear() {
    int result = SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    if (result == -1) {
        throw SdlError();
    }

    result = SDL_RenderClear(sdl_renderer.get());
    if (result == -1) {
        throw SdlError();
    }
}

void Renderer::copy(SDL::Texture &texture, SDL_Rect &src_rect, SDL_Rect &dst_rect) const {
    int result = SDL_RenderCopy(sdl_renderer.get(), texture.get(), &src_rect, &dst_rect);
    if (result == -1) {
        throw SdlError();
    }
}

/**
 * Use this function to update the screen with any rendering performed since the previous call.
 */
void Renderer::present() {
    SDL_RenderPresent(sdl_renderer.get());

    /* From SDL docs:
     * The backbuffer should be considered invalidated after each present; do not assume that
     * previous contents will exist between frames. You are strongly encouraged to call
     * SDL_RenderClear() to initialize the backbuffer before starting each new frame's drawing,
     * even if you plan to overwrite every pixel. */
    clear();
}

Texture Renderer::createText(const Font &font,
                             std::string text,
                             SDL_Color color) const {
    // Render text surface
    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(font.get(), text.c_str(), color);
    if (text_surface == nullptr) {
        throw SdlTtfError("Unable to render text surface!");
    }

    // Create texture from surface pixels
    SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer.get(), text_surface);
    if (sdl_texture == nullptr) {
        throw SdlError("Unable to create texture from rendered text!");
    }

    // Get image dimensions
    int width = text_surface->w;
    int height = text_surface->h;

    // Get rid of old surface
    SDL_FreeSurface(text_surface);

    return Texture(sdl_texture, width, height);
}

Texture Renderer::load(std::string path) const {
    SDL_Texture *sdl_texture = nullptr;

    // Load image at specified path
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == nullptr) {
        throw SdlImgError("Unable to load image " + path);
    }

    // Create texture from surface pixels
    sdl_texture = SDL_CreateTextureFromSurface(this->get(), loaded_surface);
    if (sdl_texture == nullptr) {
        throw SdlError("Unable to create texture from surface from " + path);
    }

    // Get image dimensions
    int width = loaded_surface->w;
    int height = loaded_surface->h;

    // Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);

    return Texture(sdl_texture, width, height);
}

SDL_Renderer *Renderer::get() const {
    return sdl_renderer.get();
}