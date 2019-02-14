#include "VertexBufferLayout.hpp"

#include "Shader.hpp"

namespace gl {

    VertexBufferLayout& VertexBufferLayout::genFromShaderAttrib(const gl::Shader& shader) {
        if (stride)
            logWarn("gl::vbl::genFromShaderAttrib() - layout isn't empty! ... ignoring");

        int count;
        GLCall(glGetProgramiv(shader.programID, GL_ACTIVE_ATTRIBUTES, &count));

        int bufferSize;
        GLCall(glGetProgramiv(shader.programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufferSize));

        logInfo("gl::vbl::baseOnShader() - Generating layout based on shader attributes!");
        logInfo("gl::vbl::baseOnShader() - Attributes count:",count,"...\nFound:");

        for (unsigned int i = 0; i < count ;i++) {

            char name[bufferSize];

            unsigned int type;
            int size, nameLength;

            glGetActiveAttrib(shader.programID, i, bufferSize, &nameLength, &size, &type, name);

            logInfo("> { name:",&name[0],", type:",type,", size:",size,"}");

            switch(type) {
                case GL_FLOAT:        this->push(1, GL_FLOAT);        continue;
                case GL_FLOAT_VEC2: case GL_FLOAT_VEC3: case GL_FLOAT_VEC4:
                this->push((type - GL_FLOAT_VEC2) + 2, GL_FLOAT);
                continue;

                case GL_INT:          this->push(1, GL_INT);          continue;
                case GL_INT_VEC2: case GL_INT_VEC3: case GL_INT_VEC4:
                this->push((type - GL_INT_VEC2) + 2, GL_INT);
                continue;

                case GL_UNSIGNED_INT: this->push(1, GL_UNSIGNED_INT); continue;
                case GL_UNSIGNED_INT_VEC2: case GL_UNSIGNED_INT_VEC3: case GL_UNSIGNED_INT_VEC4:
                this->push((type - GL_UNSIGNED_INT_VEC2) + 2, GL_UNSIGNED_INT);
                continue;
            }
            
        }
        logInfo("gl::vbl::baseOnShader() - gen done! Layout:", this->getScheme());

        return *this;
    }

    VertexBufferLayout& VertexBufferLayout::operator += (const LayoutElement& element) {
        list.push_back(element);
        stride += list.back().count * list.back().getTypeSize();
        return *this;
    }

    VertexBufferLayout& VertexBufferLayout::operator << (const LayoutElement& element) {
        *this += element;
        return *this;
    }

    LayoutElement VertexBufferLayout::operator -- () {
        LayoutElement tmp(list.back());
        this->list.pop_back();
        return tmp;
    }

    VertexBufferLayout& VertexBufferLayout::push(unsigned int count, unsigned int type, bool normalized) {
        *this += {count,type,normalized};
        return *this;
    }

    std::string VertexBufferLayout::getScheme() const {
        std::string tmp = "";
        for (const LayoutElement& i : list) {
            if (tmp != "")
                tmp += " | ";
            tmp += std::to_string(i.count) + "x";
            switch (i.type) {
                case GL_FLOAT:
                    tmp += "Float";
                break;
                case GL_DOUBLE:
                    tmp += "Double";
                break;
                case GL_UNSIGNED_BYTE:
                    tmp += "Uint";
                break;
                case GL_UNSIGNED_INT:
                    tmp += "Uchar";
                break;
                case GL_BYTE:
                    tmp += "Int";
                break;
                case GL_INT:
                    tmp += "Char";
                break;
            }
        }
        return tmp;
    }

};