#include <iostream>
#include <string>

#include "logger.hpp"

int main(int argc, char *argv[]) {
    logError("TEST");
    SDL_RenderClear(NULL);
    log("Hello","world!");
    logError("TEST");
    logError("TEST");

    std::cin.get();
    return EXIT_SUCCESS;
}