#pragma once

#include <iostream>
#include <sstream>
#include "include/sdl2.hpp"
#include "include/glew.hpp"



/* config */

#define DEBUG //TODO: DEBUG in cmake

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

inline void _raw() {}

template<typename T, typename ... T2>
inline void _raw(const T& arg, const T2& ... args) {
    _print(arg, args...);
}

/* get GL Error*/
std::string getErrorMsg(unsigned int code);

/* show pb2e asci-art */
void showLogo(void);


/////////////////////////////
//logging macros

#ifdef DEBUG

    template<typename T, typename ... T2>
    inline void _raw(const T& arg, const T2& ... args);
    void setConsoleColor(unsigned char a);

    #define cppToString(x) #x

    /* Info */
    #define logInfo(args...) _logInfo(args, " :", __FILE__, "\b:",__LINE__)

    template<typename ... T>
    inline void _logInfo(const T&...args) {
        setConsoleColor(15);
        _raw(args...);
    }

    /* Warn */
    #define logWarn(args...) _logWarn(args, " :", __FILE__, "\b:",__LINE__)

    template<typename ... T>
    inline void _logWarn(const T&...args) {
        setConsoleColor(14);
        _raw(args...);
    }

    /* Error */
    #define logError(args...) _logError(args, " :", __FILE__, "\b:",__LINE__)

    template<typename ... T>
    inline void _logError(const T&...args) {
        setConsoleColor(12);

        if ('\0' != *SDL_GetError()) {
            _raw(args..., "\n", SDL_GetError());
            SDL_ClearError();
        } else
            _raw(args...);

    }

    #define GLCall(x) while(glGetError() != GL_NO_ERROR) {}\
    x;\
    while (unsigned int code = glGetError())\
    _raw( #x, "-" , getErrorMsg(code), "at", __FILE__, "\b:",__LINE__)\

#else

    #define cppToString(x) ""
    #define logInfo(args...);
    #define logWarn(args...);
    #define logError(args...);
    #define GLCall(x) x

#endif //else DEBUG
