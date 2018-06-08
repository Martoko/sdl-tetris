#ifndef TETRIS_CPP_SDL2_TETRISAPP_HPP
#define TETRIS_CPP_SDL2_TETRISAPP_HPP

#include <memory>
#include "sdl/App.hpp"
#include "TetrisWindow.hpp"
#include "TetrominoBag.hpp"
#include "engine/ObjectList.hpp"
#include "TetrisGame.hpp"

class TetrisApp : public SDL::App {
    TetrisGame *game;

public:
    TetrisApp();

    void run();

    ~TetrisApp() override;
};


#endif //TETRIS_CPP_SDL2_TETRISAPP_HPP
