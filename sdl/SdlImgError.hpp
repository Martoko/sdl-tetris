#ifndef TETRIS_CPP_SDL2_SDLIMGERROR_HPP
#define TETRIS_CPP_SDL2_SDLIMGERROR_HPP

#include <string>

class SdlImgError : std::exception {
    std::string msg;

public:
    SdlImgError(std::string msg = "");

    const char *what() const noexcept override;
};


#endif //TETRIS_CPP_SDL2_SDLIMGERROR_HPP
