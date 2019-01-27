#include "VertexBuffer.hpp"

#include "../logger.hpp"
#include "../include/glew.hpp"

namespace gl {

    VertexBuffer::VertexBuffer(const VertexBuffer& other)
	 : VertexBuffer(other.vbl) {

        /* coping the data */

        if (other.dataSize == 0)
            return;

        data = (void*)realloc((void*)data, other.dataSize);
        memcpy(data, other.data, other.dataSize);
        
    }

    VertexBuffer::VertexBuffer(const VertexBufferLayout& vbl) : vbl(vbl) {

        /* some gl stuff */

        GLCall(glGenVertexArrays(1, &VAOID));
        GLCall(glBindVertexArray(VAOID));

        GLCall(glGenBuffers(1, &BufferID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));

        /*  layout setting  */
        
        int offset = 0;
        for (int i = 0; i < this->vbl.list.size(); i++) {

            GLCall(glVertexAttribPointer(i , this->vbl.list[i].count , this->vbl.list[i].type , (int)this->vbl.list[i].normalized , this->vbl.stride , (const void*)offset));
            GLCall(glEnableVertexAttribArray(i));

            offset += this->vbl.list[i].count * this->vbl.list[i].getTypeSize();

        }

        data = nullptr;

    }

    VertexBuffer::~VertexBuffer() {
        
        GLCall(glDeleteBuffers(1, &BufferID));
        GLCall(glDeleteBuffers(1, &VAOID));
        this->clear();
		
    }


    VertexBuffer& VertexBuffer::clear() {

        free(data);
        data = nullptr;
        dataSize = 0;

        return *this;
    }

    void VertexBuffer::use() const {
        static unsigned int lastID;

        if (lastID != VAOID) {
            lastID = VAOID;
            
            GLCall(glBindVertexArray(VAOID));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));
        }

        GLCall(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW));
    } 
};