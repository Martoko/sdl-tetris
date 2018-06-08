#pragma once

#include "sdl/App.hpp"
#include "TetrisGame.hpp"

class TetrisApp {
    SDL::App app;
    TetrisGame game;

public:
    void run();

    virtual ~TetrisApp();
};