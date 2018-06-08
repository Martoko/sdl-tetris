#pragma once

#include "../language/NonCopyableMoveable.hpp"

namespace SDL {

    class App : NonCopyableMoveable {
    public:
        App();

        ~App() override;

    private:
        void seedRandomNumberGenerator() const;

        void initSdl();

        void setTextureFilteringToLinear();

        void initSdlImage();

        void initSdlTtf() const;
    };

}