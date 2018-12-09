#pragma once

#include <vector>
#include <string>

#include "../include/glew.hpp"

namespace gl {

    /* header instead of including the whole file */
    class VertexBuffer;

    struct LayoutElement {
        unsigned int count = 0;
        unsigned int type = 0;
        bool normalized = false;

        unsigned int getTypeSize() const { //v1.1

            switch (type) {
                case GL_FLOAT:         return sizeof(GLfloat);
                case GL_DOUBLE:        return sizeof(GLdouble);
                case GL_BYTE:          return sizeof(GLbyte);
                case GL_INT:           return sizeof(GLint);
                case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
                case GL_UNSIGNED_INT:  return sizeof(GLuint);
                default:               return 0;
            }    
        }
        LayoutElement(const LayoutElement& other)
         : count(other.count), type(other.type), normalized(other.normalized) {}

        LayoutElement(unsigned int count = 0, unsigned int type = GL_FLOAT, bool normalized = false)
         : count(count), type(type), normalized(normalized) {}
    };

    class VertexBufferLayout { //v1.1
        std::vector<LayoutElement> list;
        unsigned int stride;
        public:

        VertexBufferLayout(const VertexBufferLayout&);
        VertexBufferLayout() : stride(0) {}

        VertexBufferLayout& operator += (const LayoutElement&);
        VertexBufferLayout& operator << (const LayoutElement&);
        LayoutElement operator -- ();

        VertexBufferLayout& push(unsigned int count, unsigned int type = GL_FLOAT, bool normalized = false);

        std::string getScheme() const;
        
        constexpr unsigned int getStride() const { return this->stride; }

        inline unsigned int getElementsCount() const { return this->list.size(); }

        //vertexLayout likes VertexBuffer
        friend VertexBuffer;
    };

};