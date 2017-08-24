#include <algorithm>
#include "TetrisWindow.hpp"
#include "sdl/SdlTtfError.hpp"

TetrisWindow::TetrisWindow(std::string name) : Window(name, BOARD_WIDTH, BOARD_HEIGHT) {
    tetromino_texture = SDL::Texture::fromPath(sdl_renderer, "img/tetromino.png");
    ghost_texture = SDL::Texture::fromPath(sdl_renderer, "img/tetromino_ghost.png");
    board_texture = SDL::Texture::fromPath(sdl_renderer, "img/board.png");
    dim_screen_texture = SDL::Texture::fromPath(sdl_renderer, "img/dim_screen.png");

    ubuntu_regular_20 = TTF_OpenFont("fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf", 20);
    if (ubuntu_regular_20 == NULL) {
        throw SdlTtfError("Failed to load font fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    }

    ubuntu_regular_44 = TTF_OpenFont("fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf", 44);
    if (ubuntu_regular_44 == NULL) {
        throw SdlTtfError("Failed to load font fnt/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    }

    next_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "next");
    hold_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "hold");
    score_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20, "score");
    pause_text_texture = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_44, "PAUSED",
                                                {255, 255, 255});
    game_over_title_text = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_44, "GAME OVER",
                                                  {255, 255, 255});
    game_over_description_text = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20,
                                                        "press 'R' to restart", {255, 255, 255});
}

TetrisWindow::~TetrisWindow() {
    TTF_CloseFont(ubuntu_regular_20);
    TTF_CloseFont(ubuntu_regular_44);
    delete tetromino_texture;
    delete ghost_texture;
    delete board_texture;
    delete dim_screen_texture;

    delete next_text_texture;
    delete hold_text_texture;
    delete score_text_texture;
    delete pause_text_texture;
    delete game_over_title_text;
    delete game_over_description_text;
}

void TetrisWindow::drawGameOver(int score) {
    // Draw game over img
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_RenderCopy(sdl_renderer, dim_screen_texture->sdl_texture, &src_rect, &dst_rect);

    SDL::Texture *your_score_text = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20,
                                                           "score", {255, 255, 255});
    SDL::Texture *score_value_text = SDL::Texture::fromText(sdl_renderer, ubuntu_regular_20,
                                                            std::to_string(score), {255, 255, 255});

    const int SPACING = 20;
    // The height of the invisible box containing title and description that we want to center
    int box_height = game_over_title_text->height + game_over_description_text->height
                     + your_score_text->height + SPACING + score_value_text->height;

    // Draw game over title text
    int width = game_over_title_text->width;
    int height = game_over_title_text->height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2), (BOARD_HEIGHT / 2) - (box_height / 2),
                width, height};
    SDL_RenderCopy(sdl_renderer, game_over_title_text->sdl_texture, &src_rect, &dst_rect);

    // Draw score text
    width = your_score_text->width;
    height = your_score_text->height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text->height,
                width, height};
    SDL_RenderCopy(sdl_renderer, your_score_text->sdl_texture, &src_rect, &dst_rect);

    // Draw score value text
    width = score_value_text->width;
    height = score_value_text->height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text->height
                + your_score_text->height,
                width, height};
    SDL_RenderCopy(sdl_renderer, score_value_text->sdl_texture, &src_rect, &dst_rect);

    // Draw press r to restart text
    width = game_over_description_text->width;
    height = game_over_description_text->height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text->height
                + your_score_text->height + your_score_text->height + SPACING,
                width, height};
    SDL_RenderCopy(sdl_renderer, game_over_description_text->sdl_texture, &src_rect, &dst_rect);

    delete your_score_text;
    delete score_value_text;
}

void TetrisWindow::drawPause() {
    // Draw pause img
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_RenderCopy(sdl_renderer, dim_screen_texture->sdl_texture, &src_rect, &dst_rect);

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
    SDL_RenderCopy(sdl_renderer, board_texture->sdl_texture, &src_rect, &dst_rect);

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