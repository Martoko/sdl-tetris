#ifndef TETRIS_CPP_SDL2_TETROMINO_HPP
#define TETRIS_CPP_SDL2_TETROMINO_HPP

#include <vector>
#include "Piece.hpp"
#include "Pieces.hpp"
#include "sdl/Texture.hpp"
#include "engine/Object.hpp"

class Tetromino : public Object {
    Piece pieces[4];
    int color;
    int x, y;
    int rotation = 0;
    static std::vector<std::vector<std::vector<Piece>>> all_pieces;
    SDL::Texture &texture;

public:

    Tetromino(int x, int y, int color, SDL::Texture &texture);


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

    bool outOfBounds(const int min_x, const int max_x, const int i);

    void rotate(int delta_rotation);

    void loadPieces();

    void draw(SDL::Renderer &renderer) override;
};

#endif //TETRIS_CPP_SDL2_TETROMINO_HPP
