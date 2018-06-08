#pragma once

namespace SDL {

    class Timer final {
        Uint32 start_ticks;

    public:
        Timer();

        void reset();

        Uint32 getTicks();
    };

}
