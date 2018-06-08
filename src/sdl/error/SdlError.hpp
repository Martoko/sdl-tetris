#pragma once

#include <exception>
#include <string>
#include <SDL.h>

/**
 * SdlError should only be created after SDL experiences an error
 * as it call SDL_GetError()
 */
class SdlError : public std::exception {
    std::string msg;

public:
    SdlError(std::string msg = "");

    const char *what() const noexcept override;
};