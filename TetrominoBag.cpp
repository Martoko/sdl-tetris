#include <algorithm>
#include "TetrominoBag.hpp"

int TetrominoBag::popFront() {
    if (queue.empty()) {
        addMoreToQueue();
    }

    int color = queue.front();
    queue.pop_front();
    return color;
}

int TetrominoBag::peekFront(unsigned long index) {
    while (queue.size() <= index) {
        addMoreToQueue();
    }

    int color = queue.at(index);
    return color;
}

void TetrominoBag::addMoreToQueue() {
    shuffleTetrominoColors();

    // We can't have the same color in a row, so we put it backwards to a random location
    if (!queue.empty() && queue.back() == tetromino_colors.front()) {
        auto old_index = tetromino_colors.begin();
        auto new_index = tetromino_colors.begin() + 1 + rand() % 5;
        iter_swap(old_index, new_index);
    }

    for (auto &&tetromino_color : tetromino_colors) {
        queue.push_back(tetromino_color);
    }
}

void TetrominoBag::shuffleTetrominoColors() {
    std::random_shuffle(tetromino_colors.begin(), tetromino_colors.end());
}
