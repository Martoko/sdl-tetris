
#include "TetrisApp.hpp"

TetrisApp::TetrisApp() {
    game = new TetrisGame();
}


TetrisApp::~TetrisApp() {
    delete game;
    Resources::clear();
}

void TetrisApp::run() {
    game->run();
}
