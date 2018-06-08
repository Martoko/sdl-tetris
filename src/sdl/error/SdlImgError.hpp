#pragma once

#include <string>

class SdlImgError : public std::exception {
    std::string msg;

public:
    SdlImgError(std::string msg = "");

    const char *what() const noexcept override;
};
