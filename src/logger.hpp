#pragma once

#include <iostream>
#include <sstream>
#include "include/sdl2.hpp"
#include "include/glew.hpp"

//#define GL_OUT_OF_MEMORY 0x0505
//#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
//#define GL_INVALID_OPERATION 0x0502
//#define GL_INVALID_VALUE 0x0501
//#define GL_INVALID_ENUM 0x0500
//#define GL_NO_ERROR 0

#define DEBUG

#ifdef DEBUG
#define logInfo(args...) _raw(args, " :", __FILE__, "\b:",__LINE__)

#define logError(args...) if('\0' != *SDL_GetError()){\
_raw(args, " at", __FILE__, "\b:", __LINE__, "\n", SDL_GetError());\
SDL_ClearError();\
}else \
_raw(args, " at", __FILE__, "\b:",__LINE__)

#define GLCall(x) while(glGetError() != GL_NO_ERROR) {}\
x;\
while (unsigned int code = glGetError())\
_raw( #x, "-" , getErrorMsg(code), "at", __FILE__, "\b:",__LINE__)\

#else
#define logInfo(args...);
#define logError(args...);
#define GLCall(x) x
#endif

std::string getErrorMsg(unsigned int code);


#define _OUT_LOG std::cout

template<typename T>
static inline void _print(const T& arg) {
    _OUT_LOG << arg << '\n';

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

void showLogo(void);