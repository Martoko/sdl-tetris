#include <SDL.h>
#include "Timer.hpp"

using namespace SDL;

Timer::Timer() {
    reset();
}

void Timer::reset() {
    start_ticks = SDL_GetTicks();
}

Uint32 Timer::getTicks() {
    return SDL_GetTicks() - start_ticks;
}