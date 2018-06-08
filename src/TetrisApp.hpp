#pragma once

#include "sdl/App.hpp"
#include "TetrisGame.hpp"

class TetrisApp : public SDL::App {
    TetrisGame *game;

public:
    TetrisApp();

    void run();

    ~TetrisApp() override;
};