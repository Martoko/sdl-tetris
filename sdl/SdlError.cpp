#include "SdlError.hpp"

SdlError::SdlError(std::string msg) {
    this->msg = msg;
    msg.append(SDL_GetError());
}

const char *SdlError::what() const noexcept {
    return msg.c_str();
}
