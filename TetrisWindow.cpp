#include <algorithm>
#include "TetrisWindow.hpp"
#include "sdl/SdlTtfError.hpp"

TetrisWindow::TetrisWindow(std::string name) : Window(name, BOARD_WIDTH, BOARD_HEIGHT) {
    tetromino_texture = SDL::Texture::fromPath(sdl_renderer, "img/tetromino.png");
    ghost_texture = SDL::Texture::fromPath(sdl_renderer, "img/tetromino_ghost.png");
    board_img = SDL::Texture::fromPath(sdl_renderer, "img/board.png");
    pause_img = SDL::Texture::fromPath(sdl_renderer, "img/pause.png");

    ubuntu_regular_20 = TTF_OpenFont("fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf", 20);
    if (ubuntu_regular_20 == NULL) {
        throw SdlTtfError("Failed to load font fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    }

    ubuntu_regular_48 = TTF_OpenFont("fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf", 48);
    if (ubuntu_regular_48 == NULL) {
        throw SdlTtfError("Failed to load font fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    }

    next_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "next");
    hold_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "hold");
    score_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "score");
    pause_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_48, "PAUSED",
                                                {255, 255, 255});
}

TetrisWindow::~TetrisWindow() {
    TTF_CloseFont(ubuntu_regular_20);
    TTF_CloseFont(ubuntu_regular_48);
    delete tetromino_texture;
    delete ghost_texture;
    delete board_img;
    delete pause_img;

    delete next_text_texture;
    delete hold_text_texture;
    delete score_text_texture;
    delete pause_text_texture;
}

void TetrisWindow::drawPause() {
    // Draw pause img
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_RenderCopy(sdl_renderer, pause_img->sdl_texture, &src_rect, &dst_rect);

    // Draw pause text
    int width = pause_text_texture->width;
    int height = pause_text_texture->height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2), (BOARD_HEIGHT / 2) - (height / 2), width, height};
    SDL_RenderCopy(sdl_renderer, pause_text_texture->sdl_texture, &src_rect, &dst_rect);
}

void TetrisWindow::drawBackground() {
    // Draw board BG
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_RenderCopy(sdl_renderer, board_img->sdl_texture, &src_rect, &dst_rect);

    // Draw next text
    int width = next_text_texture->width;
    int height = next_text_texture->height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 13 - (height / 2), width, height};
    SDL_RenderCopy(sdl_renderer, next_text_texture->sdl_texture, &src_rect, &dst_rect);

    // Draw hold text
    width = hold_text_texture->width;
    height = hold_text_texture->height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 325 - (height / 2), width, height};
    SDL_RenderCopy(sdl_renderer, hold_text_texture->sdl_texture, &src_rect, &dst_rect);

    // Draw score text
    width = score_text_texture->width;
    height = score_text_texture->height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 200 - (height / 2), width, height};
    SDL_RenderCopy(sdl_renderer, score_text_texture->sdl_texture, &src_rect, &dst_rect);
}

void TetrisWindow::drawBoard(int (*board)[24]) {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 24; ++y) {
            if (board[x][y] != -1) {
                drawPiece(board[x][y], x, y);
            }
        }
    }
}

void TetrisWindow::drawGhost(Tetromino *tetromino) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = tetromino->getPieceX(i);
        int piece_y = tetromino->getPieceY(i);
        int color = tetromino->getColor();

        drawGhostPiece(color, piece_x, piece_y);
    }
}

void TetrisWindow::drawGhostPiece(int color, int x, int y) {
    y -= 2;
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x * 18 + 1 + 2, y * 18 + 1 + 2, 18, 18};
    SDL_RenderCopy(sdl_renderer, ghost_texture->sdl_texture, &src_rect, &dst_rect);
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

void TetrisWindow::drawNext(Tetromino *tetromino, int index) {
    drawGui(tetromino, 188, 36 + 50 * index);
}

void TetrisWindow::drawHold(Tetromino *tetromino) {
    drawGui(tetromino, 188, 351);
}

void TetrisWindow::drawGui(Tetromino *tetromino, int anchor_x, int anchor_y) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = anchor_x + tetromino->getPieceX(i) * 18;
        int piece_y = anchor_y + tetromino->getPieceY(i) * 18;
        int color = tetromino->getColor();

        if (color == 0) {
            piece_y -= 18 / 2;
        }

        if (color != 0 && color != 1) {
            piece_x += 18 / 2;
        }

        drawGuiPiece(color, piece_x, piece_y);
    }
}

void TetrisWindow::drawGuiPiece(int color, int x, int y) {
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x, y, 18, 18};
    SDL_RenderCopy(sdl_renderer, tetromino_texture->sdl_texture, &src_rect, &dst_rect);
}

void TetrisWindow::drawScoreValue(int score) {
    SDL::Texture *score_value_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20,
                                                               std::to_string(score));

    int width = score_value_texture->width;
    int height = score_value_texture->height;
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {223 - (width / 2), 224 - (height / 2), width, height};
    SDL_RenderCopy(sdl_renderer, score_value_texture->sdl_texture, &src_rect, &dst_rect);

    delete score_value_texture;
}