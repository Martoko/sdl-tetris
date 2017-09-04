#ifndef TETRIS_CPP_SDL2_TETRISWINDOW_HPP
#define TETRIS_CPP_SDL2_TETRISWINDOW_HPP


#include <vector>
#include <memory>
#include "sdl/Window.hpp"
#include "sdl/Texture.hpp"
#include "Piece.hpp"
#include "Pieces.hpp"
#include "sdl/Timer.hpp"
#include "Tetromino.hpp"
#include "sdl/Font.hpp"
#include "engine/Resources.hpp"

const int BOARD_WIDTH = 264;
const int BOARD_HEIGHT = 402;

class TetrisWindow : public SDL::Window {
    const SDL::Font *ubuntu_regular_20;
    const SDL::Font *ubuntu_regular_44;

    SDL::Texture game_over_title_text;
    SDL::Texture game_over_description_text;
    SDL::Texture score_text_texture;
    SDL::Texture next_text_texture;
    SDL::Texture hold_text_texture;
    SDL::Texture pause_text_texture;
    SDL::Texture level_text_texture;

public:
    TetrisWindow();

    void drawBoard(int board[10][24]);

    void draw(Tetromino *tetromino);

    void drawPiece(int color, int x, int y);

    void drawGhost(Tetromino *tetromino);

    void drawGhostPiece(int color, int x, int y);

    void drawHold(Tetromino *tetromino);

    void drawGuiPiece(int color, int x, int y);

    void drawGui(Tetromino *tetromino, int anchor_x, int anchor_y);

    void drawNext(Tetromino *tetromino, int index);

    void drawPause();

    void drawBackground();

    void drawScoreValue(int score);

    void drawGameOver(int score);

    void drawInstructions();

    void drawLevelValue(int level);
};


#endif //TETRIS_CPP_SDL2_TETRISWINDOW_HPP
