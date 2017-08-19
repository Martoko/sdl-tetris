#include "TetrisApp.hpp"
#include "sdl/Window.hpp"
#include "sdl/Delay.hpp"
#include "TetrisWindow.hpp"

void TetrisApp::run() {
    TetrisWindow window("Tetris", 182 + 4, 398 + 4);

    while (!window.wants_quit) {
        window.update();

        window.renderToScreen();
    }
}
