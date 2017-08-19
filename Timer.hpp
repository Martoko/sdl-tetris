#ifndef TETRIS_CPP_SDL2_TIMER_HPP
#define TETRIS_CPP_SDL2_TIMER_HPP


class Timer {
    Uint32 start_ticks;

public:
    Timer();

    void reset();

    Uint32 getTicks();
};


#endif //TETRIS_CPP_SDL2_TIMER_HPP
