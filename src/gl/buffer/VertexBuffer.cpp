#include "VertexBuffer.hpp"

#include "../../logger.hpp"
#include "../../include/glew.hpp"

namespace gl {

    VertexBuffer::VertexBuffer(const VertexBuffer& other)
	 : VertexBuffer(other.vbl)
    {
        /* copying data */

        if (other.maxSize == 0)
            return;

        data = (void*)realloc((void*)data, other.maxSize);
        memcpy(data, other.data, other.maxSize);

        maxSize = other.maxSize;
        dataSize = other.dataSize;
    }

    VertexBuffer::VertexBuffer(const VertexBufferLayout& vbl)
     : vbl(vbl)
    {
        /* creating VAO & buffer */

        GLCall(glGenVertexArrays(1, &VAOID));
        GLCall(glBindVertexArray(VAOID));

        GLCall(glGenBuffers(1, &BufferID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));

        /*  layout setting  */
        
        int offset = 0;
        for (int i = 0; i < this->vbl.list.size(); i++)
        {

            GLCall(glVertexAttribPointer(i , this->vbl.list[i].count , this->vbl.list[i].type , (int)this->vbl.list[i].normalized , this->vbl.stride , (const void*)offset));
            GLCall(glEnableVertexAttribArray(i));

            offset += this->vbl.list[i].count * this->vbl.list[i].getTypeSize();

        }

        data = nullptr;

    }

    VertexBuffer::~VertexBuffer()
    {
        
        GLCall(glDeleteBuffers(1, &BufferID));
        GLCall(glDeleteVertexArrays(1, &VAOID));
        this->clear();
		
    }


    void VertexBuffer::reserve(unsigned int size)
    {
        maxSize += size*vbl.stride;
        data = (void*)realloc((void*)data, maxSize);
    }

    VertexBuffer& VertexBuffer::clear()
    {

        free(data);
        data = nullptr;
        dataSize = 0;
        maxSize = 0;

        return *this;
    }

    void VertexBuffer::use() const
    {
        static unsigned int lastID;

        if (lastID != VAOID)
        {
            lastID = VAOID;
            
            GLCall(glBindVertexArray(VAOID));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));
        }

        GLCall(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW));
    } 
};