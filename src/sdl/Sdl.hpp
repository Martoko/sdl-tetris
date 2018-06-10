#pragma once

#include "../language/NonCopyableMoveable.hpp"
#include "Window.hpp"

namespace SDL {

    class Sdl : NonCopyableMoveable {
    public:
        Sdl();

        ~Sdl() override;

    private:
        void initSdl();

        void setTextureFilteringToLinear();

        void initSdlImage();

        void initSdlTtf() const;
    };

}