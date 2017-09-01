#include <SDL_image.h>
#include "SdlImgError.hpp"

SdlImgError::SdlImgError(std::string msg) {
    this->msg = msg;
    msg.append(IMG_GetError());
}

const char *SdlImgError::what() const noexcept {
    return msg.c_str();
}
