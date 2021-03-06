#pragma once

#include <vector>
#include "Piece.hpp"

class Tetromino {
    Piece pieces[4];
    int color;
    int x, y;
    int rotation = 0;
    static std::vector<std::vector<std::vector<Piece>>> all_pieces;

public:
    Tetromino(int x, int y, int color);

    int getColor() const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    int getRotation() const;

    void setRotation(int rotation);

    int getPieceX(unsigned int i) const;

    int getPieceY(unsigned int i) const;

    void setColor(int color);

    bool collidesWithBoard(int board[10][24]);

    void move(int dx, int dy);

    bool outOfBounds(int min_x, int max_x, int i);

    void rotate(int delta_rotation);

    void updatePieces();
};
