#include <SDL_ttf.h>
#include "SdlTtfError.hpp"

SdlTtfError::SdlTtfError(std::string msg) {
    this->msg = msg;
    msg.append(TTF_GetError());
}

const char *SdlTtfError::what() const noexcept {
    return msg.c_str();
}
