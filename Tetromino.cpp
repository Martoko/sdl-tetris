#include <stdexcept>
#include "Tetromino.hpp"

std::vector<std::vector<std::vector<Piece>>> Tetromino::all_pieces = getPieces();

Tetromino::Tetromino(int x, int y, int color) : color(color), x(x), y(y) {
    loadPieces();
}

void Tetromino::loadPieces() {
    for (int i = 0; i < 4; ++i) {
        pieces[i] = all_pieces[color][rotation][i];
    }
}

int Tetromino::getColor() const {
    return color;
}

int Tetromino::getX() const {
    return x;
}

int Tetromino::getY() const {
    return y;
}

int Tetromino::getPieceX(unsigned int i) const {
    if (i >= 4) {
        throw new std::runtime_error("Invalid index");
    }

    return x + pieces[i].x;
}

int Tetromino::getPieceY(unsigned int i) const {
    if (i >= 4) {
        throw new std::runtime_error("Invalid index");
    }

    return y + pieces[i].y;
}

bool Tetromino::collidesWithBoard(int (*board)[24]) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = getPieceX(i);
        int piece_y = getPieceY(i);

        if (board[piece_x][piece_y] != -1) {
            return true;
        }
    }

    return false;
}

void Tetromino::move(int dx, int dy) {
    x += dx;
    y += dy;
}

bool Tetromino::outOfBounds(const int min_x, const int max_x, const int max_y) {
    for (unsigned int i = 0; i < 4; ++i) {
        int piece_x = getPieceX(i);
        int piece_y = getPieceY(i);

        if (piece_x < min_x || piece_x > max_x || piece_y > max_y) {
            return true;
        }
    }

    return false;
}

void Tetromino::rotate(int delta_rotation) {
    delta_rotation %= 4;

    rotation += delta_rotation;

    if (rotation >= 4) {
        rotation = 0;
    }

    if (rotation < 0) {
        rotation = 3;
    }

    loadPieces();
}

Tetromino::Tetromino(Tetromino *tetromino) :
        Tetromino(tetromino->getX(), tetromino->getY(), tetromino->getColor()) {
}

void Tetromino::setX(int x) {
    Tetromino::x = x;
}

void Tetromino::setY(int y) {
    Tetromino::y = y;
}

int Tetromino::getRotation() const {
    return rotation;
}

void Tetromino::setRotation(int rotation) {
    rotation %= 4;
    if (rotation < 0) {
        rotation = 3 - rotation;
    }
    Tetromino::rotation = rotation;

    loadPieces();
}

void Tetromino::setColor(int color) {
    Tetromino::color = color;

    loadPieces();
}
