#include <iostream>
#include "SdlError.hpp"

SdlError::SdlError(std::string msg) {
    this->msg = msg;
    this->msg.append(". SDL_Error: ");
    this->msg.append(SDL_GetError());
    SDL_ClearError();
}

const char *SdlError::what() const noexcept {
    return msg.c_str();
}
