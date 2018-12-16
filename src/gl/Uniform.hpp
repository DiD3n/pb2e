#pragma once

#include <string>
#include "../include/glm.hpp"

template<typename T>
static void pushDataArray(T* data, const T& arg) {
    data[0] = arg; 
}

template<typename T, typename ... T2>
static void pushDataArray(T* data, const T& arg, const T2&... args) {
    data[0] = arg;
    pushDataArray(data + 1, args...);
}

namespace gl {

    enum UniformType : int { //TODO: double
        vec1f   = 0,   vec1ui  = 1,   vec1i   = 2,
        vec2f   = 20,  vec2ui  = 21,  vec2i   = 22,
        vec3f   = 30,  vec3ui  = 31,  vec3i   = 32,
        vec4f   = 40,  vec34ui = 41,  vec34   = 42,

        mat2    = 50,  mat3    = 51,  mat4    = 52,
    };

        
    //UniformType getUniformType(const std::type_info& type, int count) {
    //}

    struct Uniform {
        void* data;
        int dataCount;
        int type;
        bool pointable;

        Uniform& operator=(const Uniform& other) {
            if (other.pointable) {
                this->data = other.data;
            }
            this->pointable = other.pointable;
            return *this;
        }

        template<typename T, typename ... T2>
        Uniform(bool pointable, const T& arg, const T2&... args) {  
            if (pointable)
                logError("Uniform::Uniform() - pointable only can be used for vec1... ignoring");

            dataCount = sizeOfMulti(arg,args...)/sizeof(T);
                 if (typeid(T) == typeid(float))        this->type = (UniformType)(10 * dataCount + 0);
            else if (typeid(T) == typeid(unsigned int)) this->type = (UniformType)(10 * dataCount + 1);
            else if (typeid(T) == typeid(int))          this->type = (UniformType)(10 * dataCount + 2);

            this->pointable = false;
            data = (T*)malloc(sizeOfMulti(arg,args...));
            
            pushDataArray((T*)data,arg,args...);
        }

        template<typename T>
        Uniform(bool pointable, T& arg) {
            dataCount = 1;
                 if (typeid(T) == typeid(float))        this->type = vec1f; 
            else if (typeid(T) == typeid(int))          this->type = vec1i; 
            else if (typeid(T) == typeid(unsigned int)) this->type = vec1ui;
            else if (typeid(T) == typeid(glm::mat2))    this->type = mat2;
            else if (typeid(T) == typeid(glm::mat3))    this->type = mat3;
            else if (typeid(T) == typeid(glm::mat4))    this->type = mat4;
            if (pointable) {
                this->pointable = true;
                data = &arg;
            }
            else {
                data = malloc(sizeof(T));

                pushDataArray((T*)data,arg);
            } 
        }

        ~Uniform() {
            if (!pointable) 
                free(data);
        }
    };

};