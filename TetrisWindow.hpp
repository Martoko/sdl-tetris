#ifndef TETRIS_CPP_SDL2_TETRISWINDOW_HPP
#define TETRIS_CPP_SDL2_TETRISWINDOW_HPP


#include <vector>
#include "sdl/Window.hpp"
#include "sdl/Texture.hpp"
#include "Piece.hpp"
#include "Pieces.hpp"
#include "Timer.hpp"

class TetrisWindow : public SDL::Window {
public:
    TetrisWindow(std::string name, int width, int height);

    virtual ~TetrisWindow();

    void update();

    bool wants_quit = false;

private:
    void draw() override;

    SDL::Texture *texture;

    bool game_over = false;

    int board[10][24];

    int cur_x = 0;
    int cur_y = 0;
    Piece cur_pieces[4] = {Piece(0, 0), Piece(1, 0), Piece(2, 0), Piece(3, 0)};
    Piece ghost[4] = {Piece(0, 0), Piece(1, 0), Piece(2, 0), Piece(3, 0)};
    int cur_rot = 0;
    int cur_color = 0;

    std::vector<std::vector<std::vector<Piece>>> pieces = getPieces();

    std::vector<int> bag = {0, 1, 2, 3, 4, 5, 6};
    int bag_i = 0;

    Timer gravity_timer;

    int gravity_delay_slow = 500;

    int gravity_delay_fast = 100;

    int gravity_delay = gravity_delay_slow;

    void drawPiece(int color, int x, int y);

    void drawBoard();

    void drawCurrentTetromino();

    bool moveCurTetromino(int dx, int dy);

    void resetTetromino();

    void calculateScoring();

    bool applyGravity();

    void resetBag();

    bool rotateTetromino();

    void drawBGTile(int x, int y);

    void drawBGBorder(int x, int y);

    SDL::Texture *board_img;
    SDL::Texture *ghost_texture;

    void drawGhostPiece(int color, int x, int y);

    void drawGhostTetromino();

    bool moveGhostTetromino(int dx, int dy);

    bool rotateEdgeTetromino();
};


#endif //TETRIS_CPP_SDL2_TETRISWINDOW_HPP
