#pragma once

#include <string>

class SdlTtfError : public std::exception {
    std::string msg;

public:
    SdlTtfError(std::string msg = "");

    const char *what() const noexcept override;
};