#include "Renderer.hpp"
#include "error/SdlError.hpp"

namespace SDL {

    Renderer::Renderer(SDL_Renderer *sdl_renderer) :
            sdl_renderer(sdl_renderer, &SDL_DestroyRenderer) {}

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

    SDL_Renderer *Renderer::get() const {
        return sdl_renderer.get();
    }

    void Renderer::copy(SDL::Texture &texture, SDL_Rect &src_rect, SDL_Rect &dst_rect) {
        int result = SDL_RenderCopy(sdl_renderer.get(), texture.get(), &src_rect, &dst_rect);
        if (result == -1) {
            throw SdlError();
        }
    }

}