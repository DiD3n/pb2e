#include <iostream>
#include <string>

#include "logger.hpp"

int main(int argc, char *argv[]) {

    log("Hello","world!");

    std::cin.get();
    return EXIT_SUCCESS;
}