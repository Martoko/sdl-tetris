#include "ObjectList.hpp"

void ObjectList::add(Object *sprite) {
    objects.push_back(sprite);
}

void ObjectList::remove(Object *sprite) {
    objects.push_back(sprite);
}

void ObjectList::draw(SDL::Renderer *renderer) {
    for (auto &&object : objects) {
        object->x += x;
        object->y += y;

        object->draw(renderer);

        object->x -= x;
        object->y -= y;
    }
}