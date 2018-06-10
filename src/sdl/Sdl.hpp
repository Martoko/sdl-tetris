#pragma once

#include "../language/NonCopyableMoveable.hpp"

namespace SDL {

    class Sdl final : NonCopyableMoveable {
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