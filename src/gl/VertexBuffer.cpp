#include "VertexBuffer.hpp"



namespace gl {

    VertexBuffer::VertexBuffer(VertexBufferLayout& vbl, bool ref) {
        if (ref) {
            this->vbl = &vbl;
        } else {
            this->vbl = new VertexBufferLayout(vbl);
        }
        GLCall(glGenVertexArrays(1, &VAOID));
        GLCall(glBindVertexArray(VAOID));

        GLCall(glGenBuffers(1, &BufferID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));

        int size = 0;
        for (const gl::LayoutElement& i : this->vbl->list) {
            size += i.count * i.getTypeSize();
        } 
        
        
        int a = 0;
        for (int i = 0; i < this->vbl->list.size(); i++) {
            GLCall(glVertexAttribPointer(i , this->vbl->list[i].count , this->vbl->list[i].type , (int)this->vbl->list[i].normalized , size , (const void*)a));
            GLCall(glEnableVertexAttribArray(i));
            a += this->vbl->list[i].count * this->vbl->list[i].getTypeSize();
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
        dataSize = 0;
        return *this;
    }

    VertexBuffer& VertexBuffer::bind() {
        GLCall(glBindVertexArray(VAOID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW));
        return *this;
    }

    VertexBuffer& VertexBuffer::unBind() {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
        return *this;
    }   


};