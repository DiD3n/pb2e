#pragma once


namespace gl {

    enum UniformType : int {
        vec1f   = 0,   vec1ui  = 1,   vec1i   = 2,   vec1d = 3, 
        vec2f   = 20,  vec2ui  = 21,  vec2i   = 22,  vec2d = 23,
        vec3f   = 30,  vec3ui  = 31,  vec3i   = 32,  vec3d = 33,
        vec4f   = 40,  vec34ui = 41,  vec34   = 42,  vec4d = 43,

        mat2    = 50,  mat3    = 51,  mat4    = 52,
    };

    struct Uniform {
        void* data;
        const unsigned int size;
        UniformType type;
        const bool pointable;

        template<typename T, typename ... T2>
        Uniform(const T& arg, const T2&... args);
        template<typename T>
        Uniform(bool pointable, T& arg);
        Uniform(const Uniform&);
        ~Uniform();

    };

};

#include "Uniform.inl"