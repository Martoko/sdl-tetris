#pragma once

#include <vector>
#include <queue>

class TetrominoBag {
    std::deque<int> queue;
    std::vector<int> tetromino_colors = {0, 1, 2, 3, 4, 5, 6};

public:

    int popFront();

    int peekFront(unsigned long index = 0);

    void clear();

private:

    void addMoreToQueue();

    void shuffleTetrominoColors();
};