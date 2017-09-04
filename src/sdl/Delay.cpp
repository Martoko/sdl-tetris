#include "Delay.hpp"

using namespace SDL;

void SDL::delay(Uint32 ms) {
    SDL_Delay(ms);
}