#ifndef TETRIS_CPP_SDL2_SDLTTFERROR_HPP
#define TETRIS_CPP_SDL2_SDLTTFERROR_HPP

#include <string>

class SdlTtfError : public std::exception {
    std::string msg;

public:
    SdlTtfError(std::string msg = "");

    const char *what() const noexcept override;
};


#endif //TETRIS_CPP_SDL2_SDLTTFERROR_HPP
