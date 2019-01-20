#pragma once


namespace gl {

    enum UniformType : int { //TODO: Add double support!
        vec1f   = 0,   vec1ui  = 1,   vec1i   = 2,
        vec2f   = 20,  vec2ui  = 21,  vec2i   = 22,
        vec3f   = 30,  vec3ui  = 31,  vec3i   = 32,
        vec4f   = 40,  vec34ui = 41,  vec34   = 42,

        mat2    = 50,  mat3    = 51,  mat4    = 52,
    };

    struct Uniform {
        void* data;
        UniformType type;
        bool pointable;

        template<typename T, typename ... T2>
        Uniform(const T& arg, const T2&... args);
        template<typename T>
        Uniform(T& arg, bool pointable = false);
        ~Uniform();

        Uniform& operator=(const Uniform& other);

    };

};

#include "Uniform.inl"