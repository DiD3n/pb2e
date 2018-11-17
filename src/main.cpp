<<<<<<< HEAD
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
=======
#include <iostream>
#include <string>

#include "logger.hpp"

int main(int argc, char *argv[]) {

    log("Hello","world!");
    
    std::cin.get();
    return EXIT_SUCCESS;
>>>>>>> c369ba5835ad12c5ffaac0e9776d977ff32c9ea4
}