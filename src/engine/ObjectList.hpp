#ifndef TETRIS_CPP_SDL2_OBJECTLIST_HPP
#define TETRIS_CPP_SDL2_OBJECTLIST_HPP

#include <vector>
#include "Object.hpp"

class ObjectList : public Object {
    std::vector<Object *> objects;

public:
    void add(Object *sprite);

    void remove(Object *sprite);

    void draw(SDL::Renderer *renderer) override;
};


#endif //TETRIS_CPP_SDL2_OBJECTLIST_HPP
