#ifndef TETRIS_CPP_SDL2_APP_HPP
#define TETRIS_CPP_SDL2_APP_HPP

namespace SDL {

    class App {
    public:
        App();

        virtual ~App();

    private:

        void initSdl();

        void setTextureFilteringToLinear();

        void initSdlImage();
    };

}

#endif //TETRIS_CPP_SDL2_APP_HPP
