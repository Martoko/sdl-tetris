#include "TetrisApp.hpp"

TetrisApp::TetrisApp() {
    seedRandomNumberGenerator();
    restartGame();
}

void TetrisApp::seedRandomNumberGenerator() const {
    sranddev();
}

std::unique_ptr<Tetromino> TetrisApp::newTetrominoFromBag() {
    int color = bag.popFront();

    return std::make_unique<Tetromino>(TETROMINO_START_X, TETROMINO_START_Y, color);
}

void TetrisApp::run() {
    while (!should_quit) {
        step();

        draw();
    }
}

void TetrisApp::step() {
    propagateEvents();

    if (game_over || paused || show_instructions) {
        return;
    }

    int gravity_delay_level_adjusted = (gravity_delay - 430 * level / 20);
    if (gravity_delay_level_adjusted < 50) {
        gravity_delay_level_adjusted = 50;
    }
    if (gravity_timer.getTicks() > gravity_delay_level_adjusted && current_tetromino != nullptr) {
        bool did_move = tryApplyGravity();

        if (did_move && gravity_delay == GRAVITY_FAST_DELAY) {
            score += 1;
        }

        gravity_timer.reset();
    }
}

void TetrisApp::draw() {
    window.drawBackground();

    if (show_instructions) {
        window.drawInstructions();
        window.renderToScreen();
        return;
    }

    window.drawScoreValue(score);
    window.drawLevelValue(level);

    if (!paused || game_over) {
        window.drawBoard(board);
    }

    if (hold_tetromino != nullptr && !game_over && !paused) {
        window.drawHold(hold_tetromino.get());
    }

    if (!game_over && !paused) {
        for (int i = 0; i < 3; ++i) {
            auto *tetromino = new Tetromino(0, 0, bag.peekFront((unsigned long) i));
            window.drawNext(tetromino, i);
            delete tetromino;
        }
    }

    if (current_tetromino != nullptr && !paused) {
        window.drawGhost(ghost_tetromino.get());
        window.draw(current_tetromino.get());
    }

    if (game_over) {
        window.drawGameOver(score);
    } else if (paused) {
        window.drawPause();
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
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) paused = true;
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) paused = false;
        }
    }
}

void TetrisApp::onKeyDown(SDL_KeyboardEvent event) {
    if (game_over) {
        if (event.keysym.sym == SDLK_r) {
            restartGame();
        }

        return;
    }

    if (show_instructions) {
        show_instructions = false;
        return;
    }

    switch (event.keysym.sym) {
        case SDLK_LEFT:
            move(current_tetromino.get(), -1, 0);
            resetGhost();
            break;
        case SDLK_RIGHT:
            move(current_tetromino.get(), 1, 0);
            resetGhost();
            break;
        case SDLK_DOWN:
            gravity_delay = GRAVITY_FAST_DELAY;
            break;
        case SDLK_UP:
            rotate(current_tetromino.get(), 1);
            resetGhost();
            break;
        case SDLK_z:
            rotate(current_tetromino.get(), -1);
            resetGhost();
            break;
        case SDLK_SPACE:
            sinkTetromino();
            break;
        case SDLK_c:
            // You can't hold twice in same "round"
            if (already_switched_hold) {
                return;
            }

            if (hold_tetromino == nullptr) {
                hold_tetromino = std::move(current_tetromino);
                current_tetromino = newTetrominoFromBag();
            } else {
                hold_tetromino.swap(current_tetromino);
            }

            already_switched_hold = true;

            hold_tetromino->setX(0);
            hold_tetromino->setY(0);
            hold_tetromino->setRotation(0);

            current_tetromino->setX(TETROMINO_START_X);
            current_tetromino->setY(TETROMINO_START_Y);
            current_tetromino->setRotation(0);

            resetGhost();
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
    bool did_move = tryApplyGravity();
    while (did_move) {
        score += 2;
        did_move = tryApplyGravity();
    }
}

/**
 * @return a bool of whether or not it succeeded in moving the block
 */
bool TetrisApp::tryApplyGravity() {
    bool did_move = move(current_tetromino.get(), 0, 1);
    if (!did_move) {

        for (unsigned int i = 0; i < 4; ++i) {
            int piece_x = current_tetromino->getPieceX(i);
            int piece_y = current_tetromino->getPieceY(i);
            board[piece_x][piece_y] = current_tetromino->getColor();
        }


        current_tetromino = newTetrominoFromBag();
        already_switched_hold = false;
        gravity_timer.reset();
        clearLines();
        resetGhost();

        if (current_tetromino->collidesWithBoard(board)) {
            game_over = true;

            current_tetromino.reset();
        }


        return false;
    }

    return true;
}

bool TetrisApp::move(Tetromino *tetromino, int dx, int dy) {
    if (tetromino == nullptr) {
        throw std::runtime_error("null tetromino");
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

void TetrisApp::rotate(Tetromino *tetromino, int amount) {
    // First we try to rotate in place
    if (tryRotate(tetromino, amount)) {
        return;
    }

    // If that fails we try to move it +/- up to 2 x, and see if rotation works then
    tetromino->move(1, 0);
    if (tryRotate(tetromino, amount)) {
        return;
    }

    tetromino->move(1, 0);
    if (tryRotate(tetromino, amount)) {
        return;
    }

    tetromino->move(-3, 0);
    if (tryRotate(tetromino, amount)) {
        return;
    }
    tetromino->move(-1, 0);
    if (tryRotate(tetromino, amount)) {
        return;
    }

    // Reset movement to initial state
    tetromino->move(2, 0);
}

bool TetrisApp::tryRotate(Tetromino *tetromino, int amount) {
    tetromino->rotate(amount);
    if (tetromino->collidesWithBoard(board)
        || tetromino->outOfBounds(BOARD_MIN_X, BOARD_MAX_X, BOARD_MAX_Y)) {
        tetromino->rotate(-amount);
        return false;
    } else {
        return true;
    }
}

void TetrisApp::resetGhost() {
    ghost_tetromino->setColor(current_tetromino->getColor());
    ghost_tetromino->setRotation(current_tetromino->getRotation());
    ghost_tetromino->setX(current_tetromino->getX());
    ghost_tetromino->setY(current_tetromino->getY());

    bool collide = false;
    while (!collide) {
        collide = !move(ghost_tetromino.get(), 0, 1);
    }
}

void TetrisApp::clearLines() {
    int lines_cleared = 0;

    for (int y = 23; y >= 0; --y) {

        bool full_line = true;
        for (int x = 0; x < 10; ++x) {

            if (board[x][y] == -1) {
                full_line = false;
            }
        }

        if (full_line) {
            lines_cleared++;
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

    const int line_clear_scores[] = {
            0,
            100,
            300,
            400,
            800
    };

    score += line_clear_scores[lines_cleared] * level;

    if (lines_cleared == 4) {
        if (last_line_clear_was_tetris) {
            score += line_clear_scores[4] / 2 * level;
        }

        last_line_clear_was_tetris = true;

    } else if (lines_cleared != 0) {
        last_line_clear_was_tetris = false;
    }

    lines_until_level_up -= lines_cleared;

    if (lines_until_level_up < 0) {
        lines_until_level_up += 10;
        level++;

        if (level > 20) {
            level = 20;
        }
    }
}

void TetrisApp::restartGame() {
    // Reset board to empty space
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 24; ++y) {
            board[x][y] = -1;
        }
    }

    current_tetromino.reset();
    hold_tetromino.reset();

    score = 0;
    level = 1;
    lines_until_level_up = 10;

    bag.clear();

    game_over = false;

    current_tetromino = newTetrominoFromBag();
    resetGhost();
    gravity_timer.reset();
}
