#pragma once

#include <string>
#include <vector>
#include <typeinfo>
#include <functional>

#include "../include/glew.hpp"
#include "VertexBuffer.hpp"
#include "Uniform.hpp"

namespace gl {

    struct UniformData {
        const std::string name;
        const int id;
        std::reference_wrapper<const Uniform> uniform;
        UniformData& operator <<(const Uniform& uniform) {
            this->uniform.operator=(std::ref(uniform));
            return *this;
        }
        UniformData(const std::string& name, const int& id, const Uniform& uniform)
         : uniform(std::ref(uniform)), name(name), id(id) {}
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
        
        void update(const std::string& name, const Uniform&);

        bool pushUniform(const std::string& name, const Uniform&);
    };
};
