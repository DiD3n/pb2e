#pragma once

#include <string>
#include <vector>
#include <typeinfo>
#include <functional>

#include "../../include/glew.hpp"
#include "../buffer/VertexBuffer.hpp"
#include "Uniform.hpp"

namespace gl
{

    struct UniformData
    {
        const std::string name;
        int id;
        Uniform* uniform;

        UniformData(const std::string& name, const int& id, const Uniform& uniform)
         : uniform(new gl::Uniform(uniform)), name(name), id(id) {}
        ~UniformData();

        void replaceUniform(const Uniform& newUniform); 
    };

    class VertexBufferLayout;

    class Shader
    {
    private:
        std::vector<UniformData> uniformList;
        bool legit;
        unsigned int programID;
        std::string vertexSourcePath, fragmentSourcePath;

        bool compile(const unsigned int&) const;

        void updateShaderUniform(const UniformData&) const;

    public:

        Shader(const Shader&);

        Shader(const std::string& vertexSourcePath, const std::string& fragmentSourcePath);
        ~Shader() {glDeleteProgram(programID);}

        constexpr bool operator ==(const Shader& other) const {
            return (programID == other.programID);
        }

        void recompile();

        constexpr bool isLegit() const {return legit;};

        void use(bool = true) const;

        void update() const; /* all */
        void update(const std::string& name) const; /* specific one */
        void update(const std::string& name, const Uniform&);

        bool pushUniform(const std::string& name, const Uniform&);

        friend VertexBufferLayout;
    };
    
}; //namespace gl
