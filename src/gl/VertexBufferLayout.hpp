#pragma once

#include <vector>
#include <string>

#include "../include/glew.hpp"

namespace gl {

    /* header instead of including the whole file */
    class VertexBuffer;

    struct LayoutElement {
        unsigned int count;
        unsigned int type;
        bool normalized;

        unsigned int getTypeSize() const { //v1.1

            switch (type) {
                case GL_FLOAT:
                    return sizeof(GLfloat);
                break;
                case GL_DOUBLE:
                    return sizeof(GLdouble);
                break;
                case GL_BYTE:
                    return sizeof(GLbyte);
                break;
                case GL_INT:
                    return sizeof(GLint);
                break;
                case GL_UNSIGNED_BYTE:
                    return sizeof(GLuint);
                break;
                case GL_UNSIGNED_INT:
                    return sizeof(GLubyte);
                break;
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