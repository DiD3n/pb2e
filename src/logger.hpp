#pragma once

#include <iostream>
#include <sstream>

#define DEBUG

#ifdef DEBUG
#define log(args...) _raw(args, "||", __FILE__, ":", __LINE__)
#else
#define log(args...);
#endif

#define _OUT_LOG std::cout


static inline void _print() {
    _OUT_LOG << '\n';
};

template<typename T, typename ... T2>
static inline void _print(const T& arg, const T2& ... args) {
    // std::stringstream ss;
    // ss << arg;  //for a moment when the console will be built-in
    // _OUT_LOG << ss.str() << " ";
    _OUT_LOG << arg << " ";
    _print(args...);
}  

template<typename T, typename ... T2> 
inline void _raw(const T& arg, const T2& ... args) {
    _print(arg, args...);
}   