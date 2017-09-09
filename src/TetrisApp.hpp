#ifndef TETRIS_CPP_SDL2_TETRISAPP_HPP
#define TETRIS_CPP_SDL2_TETRISAPP_HPP

#include <memory>
#include "sdl/App.hpp"
#include "TetrisWindow.hpp"
#include "TetrominoBag.hpp"
#include "engine/ObjectList.hpp"

class TetrisApp : public SDL::App {
    TetrisWindow *window;
    bool should_quit = false;
    bool game_over = false;
    SDL::Timer gravity_timer;
    const int GRAVITY_NORMAL_DELAY = 500;
    const int GRAVITY_FAST_DELAY = 100;
    int gravity_delay = GRAVITY_NORMAL_DELAY;
    std::unique_ptr<Tetromino> current_tetromino;
    std::unique_ptr<Tetromino> ghost_tetromino;
    std::unique_ptr<Tetromino> hold_tetromino;
    int board[10][24];
    bool paused = true;
    bool last_line_clear_was_tetris = false;
    int lines_until_level_up = 0;
    int score = 0;
    bool already_switched_hold = false;
    bool show_instructions = true;
    int level = 1;

    TetrominoBag bag;

    const int BOARD_MIN_X = 0;
    const int BOARD_MAX_X = 9;
    const int BOARD_MAX_Y = 23;

    const int TETROMINO_START_X = 3;
    const int TETROMINO_START_Y = 2;

public:
    TetrisApp();

    virtual ~TetrisApp();

    void run();

    void step();

    void propagateEvents();

    void onKeyDown(SDL_KeyboardEvent event);

    void onKeyUp(SDL_KeyboardEvent event);

    bool tryApplyGravity();

    void sinkTetromino();

    bool move(Tetromino *tetromino, int dx, int dy);

    void draw();

    std::unique_ptr<Tetromino> newTetrominoFromBag();

    void rotate(Tetromino *tetromino, int amount);

    bool tryRotate(Tetromino *tetromino, int amount);

    void clearLines();

    void resetGhost();

    void restartGame();
};


#endif //TETRIS_CPP_SDL2_TETRISAPP_HPP
