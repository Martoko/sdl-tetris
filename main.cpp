#include "TetrisApp.hpp"


int main(int argc, char *argv[]) {
    TetrisApp *app = new TetrisApp();

    try {
        app->run();

    } catch (std::exception &error) {
        printf("Error: %s\n", error.what());

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred",
                                 error.what(), NULL);

        return 1;
    }

    delete app;
    return 0;
}