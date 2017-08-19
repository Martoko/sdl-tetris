#include "TetrisApp.hpp"
#include "sdl/Window.hpp"
#include "sdl/Delay.hpp"

void TetrisApp::run() {
    SDL::Window window("Tetris");
    SDL::Surface *surface = window.getSurface();

    surface->clear();

    window.renderToScreen();

    SDL::delay(2000);
}
