#pragma once

#include <string>
#include <vector>

#include "../include/glew.hpp"
#include "VertexBuffer.hpp"

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

        matx2   = 50,  matx3   = 51,  matx4   = 52,

        mat2x3  = 53,  mat3x2  = 54,
        mat2x4  = 55,  mat4x2  = 56,
        mat3x4  = 57,  mat4x3  = 58
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
        Uniform(bool pointable, const T& arg) {
            dataCount = 0;
                 if (typeid(T) == typeid(float))        this->type = vec1f; 
            else if (typeid(T) == typeid(int))          this->type = vec1i; 
            else if (typeid(T) == typeid(unsigned int)) this->type = vec1ui;
                // todo: matrix support
            if (pointable) {
                this->pointable = true;
                data = &data;
            }
            else {
                data = malloc(sizeof(T));
                //new T data
                pushDataArray((T*)data,arg);
            } 
                

        }

        ~Uniform() {
            if (!pointable) 
                free(data);
        }
    };

    struct UniformData {
        const std::string name;
        const int id;
        Uniform uniform;
    };

    class Shader {
        private:
        std::vector<UniformData> uniformList;
        bool legit;
        unsigned int programID;
        std::string vertexSourcePath, fragmentSourcePath;

        bool compile(const unsigned int&);

        void updateShaderUniform(const UniformData&);

        public:

        Shader(const Shader&);

        Shader(const std::string& vertexSourcePath, const std::string& fragmentSourcePath);
        ~Shader() {glDeleteProgram(programID);}

        void recompile();

        bool isLegit();

        void bind()   {if (legit) glUseProgram(programID);}
        void unBind() {glUseProgram(0);}

        void update(); /* all */
        void update(const std::string& name); /* specific one */
        
        void update(const std::string& name, Uniform& data); /* push Data */

        bool pushUniform(const std::string& name, int type, Uniform& data);
    };
};
