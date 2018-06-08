
#include "TetrisApp.hpp"

TetrisApp::~TetrisApp() {
    Resources::clear();
}

void TetrisApp::run() {
    game.run();
}
