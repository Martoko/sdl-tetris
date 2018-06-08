#include <algorithm>
#include "TetrisWindow.hpp"

TetrisWindow::TetrisWindow() :
        Window("Tetris", BOARD_WIDTH, BOARD_HEIGHT) {}

void TetrisWindow::drawInstructions() {
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    renderer.copy(*Resources::getTexture("instructions.png"), src_rect, dst_rect);
}

void TetrisWindow::drawGameOver(int score) {
    // Draw game over images
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    renderer.copy(*Resources::getTexture("dim_screen.png"), src_rect, dst_rect);

    SDL::Texture your_score_text =
            SDL::Texture::fromText(renderer, ubuntu_regular_20, "score", {255, 255, 255});
    SDL::Texture score_value_text =
            SDL::Texture::fromText(renderer, ubuntu_regular_20, std::to_string(score),
                                   {255, 255, 255});

    const int SPACING = 20;
    // The height of the invisible box containing title and description that we want to center
    int box_height = game_over_title_text.height + game_over_description_text.height
                     + your_score_text.height + SPACING + score_value_text.height;

    // Draw game over title text
    int width = game_over_title_text.width;
    int height = game_over_title_text.height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2), (BOARD_HEIGHT / 2) - (box_height / 2),
                width, height};
    renderer.copy(game_over_title_text, src_rect, dst_rect);

    // Draw score text
    width = your_score_text.width;
    height = your_score_text.height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text.height,
                width, height};
    renderer.copy(your_score_text, src_rect, dst_rect);

    // Draw score value text
    width = score_value_text.width;
    height = score_value_text.height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text.height
                + your_score_text.height,
                width, height};
    renderer.copy(score_value_text, src_rect, dst_rect);

    // Draw press r to restart text
    width = game_over_description_text.width;
    height = game_over_description_text.height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2),
                (BOARD_HEIGHT / 2) - (box_height / 2) + game_over_title_text.height
                + your_score_text.height + your_score_text.height + SPACING,
                width, height};
    renderer.copy(game_over_description_text, src_rect, dst_rect);
}

void TetrisWindow::drawPause() {
    // Draw pause images
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    renderer.copy(*Resources::getTexture("dim_screen.png"), src_rect, dst_rect);

    // Draw pause text
    int width = pause_text_texture.width;
    int height = pause_text_texture.height;
    src_rect = {0, 0, width, height};
    dst_rect = {(BOARD_WIDTH / 2) - (width / 2), (BOARD_HEIGHT / 2) - (height / 2), width, height};
    renderer.copy(pause_text_texture, src_rect, dst_rect);
}

void TetrisWindow::drawBackground() {
    // Draw board BG
    SDL_Rect src_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_Rect dst_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    renderer.copy(*Resources::getTexture("board.png"), src_rect, dst_rect);

    // Draw next text
    int width = next_text_texture.width;
    int height = next_text_texture.height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 13 - (height / 2), width, height};
    renderer.copy(next_text_texture, src_rect, dst_rect);

    // Draw score text
    width = score_text_texture.width;
    height = score_text_texture.height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 200 - (height / 2), width, height};
    renderer.copy(score_text_texture, src_rect, dst_rect);

    // Draw level text
    width = level_text_texture.width;
    height = level_text_texture.height;
    src_rect = {0, 0, width, height};
    dst_rect = {223 - (width / 2), 260 - (height / 2), width, height};
    renderer.copy(level_text_texture, src_rect, dst_rect);
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
    renderer.copy(*Resources::getTexture("tetromino_ghost.png"), src_rect, dst_rect);
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
    renderer.copy(*Resources::getTexture("tetromino.png"), src_rect, dst_rect);
}

void TetrisWindow::drawNext(Tetromino *tetromino, int index) {
    drawGui(tetromino, 188, 36 + 50 * index);
}

void TetrisWindow::drawHold(Tetromino *tetromino) {
    // Draw hold text
    int width = hold_text_texture.width;
    int height = hold_text_texture.height;
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {223 - (width / 2), 325 - (height / 2), width, height};
    renderer.copy(hold_text_texture, src_rect, dst_rect);

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
    renderer.copy(*Resources::getTexture("tetromino.png"), src_rect, dst_rect);
}

void TetrisWindow::drawScoreValue(int score) {
    SDL::Texture score_value_texture =
            SDL::Texture::fromText(renderer, ubuntu_regular_20, std::to_string(score));

    int width = score_value_texture.width;
    int height = score_value_texture.height;
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {223 - (width / 2), 224 - (height / 2), width, height};
    renderer.copy(score_value_texture, src_rect, dst_rect);

}

void TetrisWindow::drawLevelValue(int level) {
    SDL::Texture level_value_texture =
            SDL::Texture::fromText(renderer, ubuntu_regular_20, std::to_string(level));

    int width = level_value_texture.width;
    int height = level_value_texture.height;
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {223 - (width / 2), 284 - (height / 2), width, height};
    renderer.copy(level_value_texture, src_rect, dst_rect);
}
