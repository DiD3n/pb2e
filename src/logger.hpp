#pragma once

#include <iostream>
#include <sstream>
#include "include/sdl2.hpp"

#define DEBUG

#ifdef DEBUG
#define log(args...) _raw(args, " :", __FILE__, "\b:",__LINE__)

#define logError(args...) if('\0' != *SDL_GetError()){\
_raw(args, " at", __FILE__, "\b:", __LINE__, "\n", SDL_GetError());\
SDL_ClearError();\
}else \
_raw(args, " at", __FILE__, "\b:",__LINE__)

#else
#define log(args...);
#define logError(args...);
#endif

#define _OUT_LOG std::cout

static inline void _print() {
    _OUT_LOG << '\n';
}

template<typename T, typename ... T2>
static inline void _print(const T& arg, const T2& ... args) {
    // std::stringstream ss;
    // ss << arg;
    // _OUT_LOG << ss.str() << " ";
    _OUT_LOG << arg << " ";
    _print(args...);
}  

template<typename T, typename ... T2> 
inline void _raw(const T& arg, const T2& ... args) {
    _print(arg, args...);
}   