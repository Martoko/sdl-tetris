#include <algorithm>
#include "TetrisWindow.hpp"
#include "sdl/Texture.hpp"

TetrisWindow::TetrisWindow(std::string name, int width, int height) : Window(name, width, height) {
    texture = SDL::Texture::fromPath(sdl_renderer, "tetromino.png");
    ghost_texture = SDL::Texture::fromPath(sdl_renderer, "tetromino_ghost.png");
    board_img = SDL::Texture::fromPath(sdl_renderer, "board.png");

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 24; ++y) {
            board[x][y] = -1;
        }
    }

    resetBag();
    resetTetromino();
    gravity_timer.reset();
}

void TetrisWindow::update() {
    if (gravity_timer.getTicks() > gravity_delay && !game_over) {
        applyGravity();
        gravity_timer.reset();
    }

    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            wants_quit = true;
        } else if (e.type == SDL_KEYDOWN && !game_over) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    moveCurTetromino(-1, 0);
                    break;
                case SDLK_RIGHT:
                    moveCurTetromino(1, 0);
                    break;
                case SDLK_DOWN:
                    gravity_delay = gravity_delay_fast;
                    break;
                case SDLK_UP:
                    rotateEdgeTetromino();
                    break;
                case SDLK_SPACE:
                    bool collide = false;
                    while (!collide) {
                        collide = applyGravity();
                    }
                    break;
            }
        } else if (e.type == SDL_KEYUP && !game_over) {
            switch (e.key.keysym.sym) {
                case SDLK_DOWN:
                    gravity_delay = gravity_delay_slow;
                    break;
            }
        }
    }
}

bool TetrisWindow::applyGravity() {
    bool did_move = moveCurTetromino(0, 1);
    if (!did_move) {
        for (auto &&piece: cur_pieces) {
            board[cur_x + piece.x][cur_y + piece.y] = cur_color;
        }

        resetTetromino();
        calculateScoring();

        // If reset collides
        if (!moveCurTetromino(0, 0)) {
            game_over = true;
        }

        return true;
    }

    return false;
}

void TetrisWindow::draw() {
    SDL_SetRenderDrawColor(sdl_renderer, 146, 146, 146, 0xFF);
    SDL_RenderClear(sdl_renderer);
    drawBoard();

    if (!game_over) {
        drawCurrentTetromino();
        drawGhostTetromino();
    }
}

void TetrisWindow::drawPiece(int color, int x, int y) {
    y -= 2;
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x * 18 + 1 + 2, y * 18 + 1 + 2, 18, 18};
    SDL_RenderCopy(sdl_renderer, texture->sdl_texture, &src_rect, &dst_rect);
}

void TetrisWindow::drawGhostPiece(int color, int x, int y) {
    y -= 2;
    SDL_Rect src_rect = {18 * color, 0, 18, 18};
    SDL_Rect dst_rect = {x * 18 + 1 + 2, y * 18 + 1 + 2, 18, 18};
    SDL_RenderCopy(sdl_renderer, ghost_texture->sdl_texture, &src_rect, &dst_rect);
}

TetrisWindow::~TetrisWindow() {
    delete texture;
    delete board_img;
}

void TetrisWindow::drawBoard() {
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

void TetrisWindow::drawCurrentTetromino() {
    for (auto &&cur_piece : cur_pieces) {
        drawPiece(cur_color, cur_x + cur_piece.x, cur_y + cur_piece.y);
    }
}

bool TetrisWindow::moveCurTetromino(int dx, int dy) {
    for (auto &&piece : cur_pieces) {
        int new_x = cur_x + piece.x + dx;
        int new_y = cur_y + piece.y + dy;

        if (new_x >= 10 || new_x < 0) {
//            printf("x(%i) out of bounds\n", new_x);
            return false;
        }

        if (new_y >= 24 || new_y < 0) {
//            printf("y(%i) out of bounds\n", new_y);
            return false;
        }

        if (board[new_x][new_y] != -1) {
//            printf("%i, %i not empty, is %i\n", piece.x + dx, piece.y + dy,
//                   board[piece.x + dx][piece.y + dy]);
            return false;
        }
    }

    cur_x += dx;
    cur_y += dy;

    return true;
}

bool TetrisWindow::moveGhostTetromino(int dx, int dy) {
    for (auto &&piece : ghost) {
        int new_x = piece.x + dx;
        int new_y = piece.y + dy;

        if (new_x >= 10 || new_x < 0) {
//            printf("x(%i) out of bounds\n", new_x);
            return false;
        }

        if (new_y >= 24 || new_y < 0) {
//            printf("y(%i) out of bounds\n", new_y);
            return false;
        }

        if (board[new_x][new_y] != -1) {
//            printf("%i, %i not empty, is %i\n", piece.x + dx, piece.y + dy,
//                   board[piece.x + dx][piece.y + dy]);
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        int new_x = ghost[i].x + dx;
        int new_y = ghost[i].y + dy;

        ghost[i].x = new_x;
        ghost[i].y = new_y;
    }

    return true;
}

bool TetrisWindow::rotateEdgeTetromino() {
    bool didRotate = rotateTetromino();

    if (!didRotate) {
        cur_x++;
        didRotate = rotateTetromino();
        if (!didRotate) {
            cur_x++;
            didRotate = rotateTetromino();
            if (!didRotate) {
                cur_x -= 2;
            }
        }
    }

    if (!didRotate) {
        cur_x--;
        didRotate = rotateTetromino();
        if (!didRotate) {
            cur_x--;
            didRotate = rotateTetromino();
            if (!didRotate) {
                cur_x += 2;
            }
        }
    }


    return didRotate;
}

bool TetrisWindow::rotateTetromino() {
    int new_rot = cur_rot + 1;
    if (new_rot > 3) {
        new_rot = 0;
    }

    for (int i = 0; i < 4; ++i) {
        int new_x = cur_x + pieces[cur_color][new_rot][i].x;
        int new_y = cur_y + pieces[cur_color][new_rot][i].y;

        if (new_x >= 10 || new_x < 0) {
//            printf("x(%i) out of bounds\n", new_x);
            return false;
        }

        if (new_y >= 24 || new_y < 0) {
//            printf("y(%i) out of bounds\n", new_y);
            return false;
        }

        if (board[new_x][new_y] != -1) {
//            printf("%i, %i not empty, is %i\n", piece.x + dx, piece.y + dy,
//                   board[piece.x + dx][piece.y + dy]);
            return false;
        }
    }

    cur_rot = new_rot;
    for (int i = 0; i < 4; ++i) {
        cur_pieces[i] = pieces[cur_color][cur_rot][i];
    }

    return true;
}

void TetrisWindow::resetTetromino() {
    cur_rot = 0;
    cur_x = 3;
    cur_y = 2;

    if (bag_i == 7) {
        resetBag();
        bag_i = 0;
    }

    cur_color = bag[bag_i];

    for (int i = 0; i < 4; ++i) {
        cur_pieces[i] = pieces[cur_color][cur_rot][i];
    }
    bag_i++;
}

void TetrisWindow::calculateScoring() {
    for (int y = 23; y >= 0; --y) {

        bool complete = true;
        for (int x = 0; x < 10; ++x) {

            if (board[x][y] == -1) {
                complete = false;
            }
        }

        if (complete) {
            printf("Scored line at %i\n", y);
            for (int x = 0; x < 10; ++x) {
                board[x][y] = -1;
            }

            for (int y2 = y; y2 > 0; --y2) {
                for (int x = 0; x < 10; ++x) {
                    if (y2 - 1 < 0) {
                        board[x][y2] = -1;
                    } else {
                        board[x][y2] = board[x][y2 - 1];
                    }
                }
            }

            if (y < 24) {
                y++;
            }
        }
    }
}

void TetrisWindow::resetBag() {
    printf("Reshuffling bag: ");
    for (auto &&item : bag) {
        printf("%i ", item);
    }
    printf("\n");
    std::random_shuffle(bag.begin(), bag.end());
    printf("New bag: ");
    for (auto &&item : bag) {
        printf("%i ", item);
    }
    printf("\n");
}

void TetrisWindow::drawGhostTetromino() {
    for (int i = 0; i < 4; ++i) {
        ghost[i].x = cur_x + cur_pieces[i].x;
        ghost[i].y = cur_y + cur_pieces[i].y;
    }

    bool did_move = true;
    while (did_move) {
        did_move = moveGhostTetromino(0, 1);
    }

    for (int i = 0; i < 4; ++i) {
        drawGhostPiece(cur_color, ghost[i].x, ghost[i].y);
    }
}
