#ifndef TETRIS_CPP_SDL2_APP_HPP
#define TETRIS_CPP_SDL2_APP_HPP

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

#endif //TETRIS_CPP_SDL2_APP_HPP
