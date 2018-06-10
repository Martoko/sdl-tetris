#pragma once

namespace SDL {

    class Timer {
        Uint32 start_ticks;

    public:
        Timer();

        void reset();

        Uint32 getTicks();
    };

}
