#ifndef TETRIS_CPP_SDL2_TETRISAPP_HPP
#define TETRIS_CPP_SDL2_TETRISAPP_HPP

#include "sdl/App.hpp"
#include "TetrisWindow.hpp"

class TetrisApp : public SDL::App {
    TetrisWindow window = TetrisWindow("Tetris", 182 + 4, 398 + 4);
    bool should_quit = false;
    bool game_over = false;
    SDL::Timer gravity_timer;
    const int GRAVITY_NORMAL_DELAY = 500;
    const int GRAVITY_FAST_DELAY = 100;
    int gravity_delay = GRAVITY_NORMAL_DELAY;
    Tetromino *current_tetromino = nullptr;
    Tetromino *ghost_tetromino = nullptr;
    int board[10][24];

    const int BOARD_MIN_X = 0;
    const int BOARD_MAX_X = 9;
    const int BOARD_MAX_Y = 23;

    std::vector<int> bag = {0, 1, 2, 3, 4, 5, 6};
    int bag_index = 0;

public:
    TetrisApp();

    void run();

    void step();

    void propagateEvents();

    void onKeyDown(SDL_KeyboardEvent event);

    void onKeyUp(SDL_KeyboardEvent event);

    bool tryApplyGravity();

    void sinkTetromino();

    bool move(Tetromino *tetromino, int dx, int dy);

    void draw();

    virtual ~TetrisApp();

    void reshuffleBag();

    Tetromino *newTetrominoFromBag();

    void rotate(Tetromino *tetromino);

    bool tryRotate(Tetromino *tetromino);

    void clearLines();

    void resetGhost();
};


#endif //TETRIS_CPP_SDL2_TETRISAPP_HPP
