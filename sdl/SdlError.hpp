#ifndef TETRIS_CPP_SDL2_SDLERROR_HPP
#define TETRIS_CPP_SDL2_SDLERROR_HPP

#include <exception>
#include <string>
#include <SDL.h>

/**
 * SdlError should only be created after SDL experiences an error
 * as it call SDL_GetError()
 */
class SdlError : std::exception {
    std::string msg;

public:
    SdlError(std::string msg = "");

    const char *what() const noexcept override;
};


#endif //TETRIS_CPP_SDL2_SDLERROR_HPP
