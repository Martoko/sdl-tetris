#include <algorithm>
#include "TetrisWindow.hpp"

TetrisWindow::TetrisWindow(std::string name, int width, int height) : Window(name, width, height) {
    tetromino_texture = SDL::Texture::fromPath(sdl_renderer, "tetromino.png");
    ghost_texture = SDL::Texture::fromPath(sdl_renderer, "tetromino_ghost.png");
    board_img = SDL::Texture::fromPath(sdl_renderer, "board.png");
}

void TetrisWindow::drawGhostPiece(int color, int x, int y) {
    y -= 2;
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x * 18 + 1 + 2, y * 18 + 1 + 2, 18, 18};
    SDL_RenderCopy(sdl_renderer, ghost_texture->sdl_texture, &src_rect, &dst_rect);
}

TetrisWindow::~TetrisWindow() {
    delete tetromino_texture;
    delete board_img;
}

void TetrisWindow::drawGhost(Tetromino *tetromino) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = tetromino->getPieceX(i);
        int piece_y = tetromino->getPieceY(i);
        int color = tetromino->getColor();

        drawGhostPiece(color, piece_x, piece_y);
    }
}

void TetrisWindow::drawBoard(int (*board)[24]) {
    SDL_Rect src_rect = {0, 0, 182, 398};
    SDL_Rect dst_rect = {0 + 2, 0 + 2, 182, 398};
    SDL_RenderCopy(sdl_renderer, board_img->sdl_texture, &src_rect, &dst_rect);

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 24; ++y) {
            if (board[x][y] != -1) {
                drawPiece(board[x][y], x, y);
            }
        }
    }
}

void TetrisWindow::draw(Tetromino *tetromino) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = tetromino->getPieceX(i);
        int piece_y = tetromino->getPieceY(i);
        int color = tetromino->getColor();

        drawPiece(color, piece_x, piece_y);
    }
}

void TetrisWindow::drawPiece(int color, int x, int y) {
    y -= 2;
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x * 18 + 1 + 2, y * 18 + 1 + 2, 18, 18};
    SDL_RenderCopy(sdl_renderer, tetromino_texture->sdl_texture, &src_rect, &dst_rect);
}

