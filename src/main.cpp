#include "TetrisApp.hpp"


int main(int argc, char *argv[]) {
    try {
        TetrisApp *app = new TetrisApp();
        app->run();
        delete app;

    } catch (std::exception &error) {
        printf("Error: %s\n", error.what());

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred", error.what(), NULL);

        return 1;
    }

    return 0;
}