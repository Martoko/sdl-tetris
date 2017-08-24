#include <lirc_client.h>
#include <stdexcept>
#include <algorithm>
#include "TetrisApp.hpp"

TetrisApp::TetrisApp() {
    // Reset board to empty space
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 24; ++y) {
            board[x][y] = -1;
        }
    }

    reshuffleBag();
    current_tetromino = newTetrominoFromBag();
    ghost_tetromino = new Tetromino(current_tetromino);
    resetGhost();
    gravity_timer.reset();
}

TetrisApp::~TetrisApp() {
    if (current_tetromino != nullptr) {
        delete current_tetromino;
    }

    if (ghost_tetromino != nullptr) {
        delete ghost_tetromino;
    }
}

Tetromino *TetrisApp::newTetrominoFromBag() {
    bag_index++;
    if (bag_index > 6) {
        reshuffleBag();
        bag_index = 0;
    }

    int color = bag[bag_index];

    const int START_X = 3;
    const int START_Y = 2;
    return new Tetromino(START_X, START_Y, color);
}

/**
 * Reshuffles the bag and resets the bag index
 */
void TetrisApp::reshuffleBag() {
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

void TetrisApp::run() {
    while (!should_quit) {
        step();

        draw();
    }
}

void TetrisApp::step() {
    propagateEvents();

    if (gravity_timer.getTicks() > gravity_delay && !game_over && current_tetromino != nullptr) {
        tryApplyGravity();
        gravity_timer.reset();
    }
}

void TetrisApp::draw() {
    window.drawBoard(board);
    if (current_tetromino != nullptr) {
        window.draw(current_tetromino);
    }
    if (ghost_tetromino != nullptr) {
        window.drawGhost(ghost_tetromino);
    }

    window.renderToScreen();
}

void TetrisApp::propagateEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            this->should_quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            onKeyDown(event.key);
        } else if (event.type == SDL_KEYUP) {
            onKeyUp(event.key);
        }
    }
}

void TetrisApp::onKeyDown(SDL_KeyboardEvent event) {
    if (game_over) {
        return;
    }

    switch (event.keysym.sym) {
        case SDLK_LEFT:
            move(current_tetromino, -1, 0);
            resetGhost();
            break;
        case SDLK_RIGHT:
            move(current_tetromino, 1, 0);
            resetGhost();
            break;
        case SDLK_DOWN:
            gravity_delay = GRAVITY_FAST_DELAY;
            break;
        case SDLK_UP:
            rotate(current_tetromino);
            resetGhost();
            break;
        case SDLK_SPACE:
            sinkTetromino();
            break;
        default:
            break;
    }
}

void TetrisApp::onKeyUp(SDL_KeyboardEvent event) {
    if (game_over) {
        return;
    }

    switch (event.keysym.sym) {
        case SDLK_DOWN:
            gravity_delay = GRAVITY_NORMAL_DELAY;
            break;
        default:
            break;
    }
}

void TetrisApp::sinkTetromino() {
    bool tetrominoMoved = true;
    while (tetrominoMoved) {
        tetrominoMoved = tryApplyGravity();
    }
}

/**
 * @return a bool of whether or not it succeeded in moving the block
 */
bool TetrisApp::tryApplyGravity() {
    printf("Doing gravity\n");
    bool did_move = move(current_tetromino, 0, 1);
    if (!did_move) {
        printf("Collision\n");

        for (unsigned int i = 0; i < 4; ++i) {
            int piece_x = current_tetromino->getPieceX(i);
            int piece_y = current_tetromino->getPieceY(i);
            board[piece_x][piece_y] = current_tetromino->getColor();
        }

        delete current_tetromino;
        current_tetromino = newTetrominoFromBag();
        ghost_tetromino = new Tetromino(current_tetromino);
        resetGhost();
        gravity_timer.reset();
        clearLines();

        if (current_tetromino->collidesWithBoard(board)) {
            printf("Game over!");
            game_over = true;

            delete current_tetromino;
            current_tetromino = nullptr;

            delete ghost_tetromino;
            ghost_tetromino = nullptr;
        }


        return false;
    }

    return true;
}

bool TetrisApp::move(Tetromino *tetromino, int dx, int dy) {
    if (tetromino == nullptr) {
        throw new std::runtime_error("null tetromino");
    }

    tetromino->move(dx, dy);
    if (tetromino->collidesWithBoard(board)
        || tetromino->outOfBounds(BOARD_MIN_X, BOARD_MAX_X, BOARD_MAX_Y)) {
        tetromino->move(-dx, -dy);
        return false;

    } else {
        return true;
    }
}

void TetrisApp::rotate(Tetromino *tetromino) {
    // First we try to rotate in place
    if (tryRotate(tetromino)) {
        return;
    }

    // If that fails we try to move it +/- up to 2 x, and see if rotation works then
    tetromino->move(1, 0);
    if (tryRotate(tetromino)) {
        return;
    }

    tetromino->move(1, 0);
    if (tryRotate(tetromino)) {
        return;
    }

    tetromino->move(-3, 0);
    if (tryRotate(tetromino)) {
        return;
    }
    tetromino->move(-1, 0);
    if (tryRotate(tetromino)) {
        return;
    }
}

bool TetrisApp::tryRotate(Tetromino *tetromino) {
    tetromino->rotate(1);
    if (tetromino->collidesWithBoard(board)
        || tetromino->outOfBounds(BOARD_MIN_X, BOARD_MAX_X, BOARD_MAX_Y)) {
        tetromino->rotate(-1);
        return false;
    } else {
        return true;
    }
}

void TetrisApp::resetGhost() {
    ghost_tetromino->setRotation(current_tetromino->getRotation());
    ghost_tetromino->setX(current_tetromino->getX());
    ghost_tetromino->setY(current_tetromino->getY());

    bool collide = false;
    while (!collide) {
        collide = !move(ghost_tetromino, 0, 1);
    }
}

void TetrisApp::clearLines() {
    for (int y = 23; y >= 0; --y) {

        bool full_line = true;
        for (int x = 0; x < 10; ++x) {

            if (board[x][y] == -1) {
                full_line = false;
            }
        }

        if (full_line) {
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
