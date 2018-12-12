#include "VertexBuffer.hpp"



namespace gl {

    VertexBuffer::VertexBuffer(VertexBufferLayout& vbl, bool ref) {
        if (ref) {
            this->vbl = &vbl;
        } else {
            this->vbl = new VertexBufferLayout(vbl);
        }
        glGenBuffers(1, &BufferID);
        //this->bind();
        data = nullptr;
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &BufferID);
        this->clear();
    }


    VertexBuffer& VertexBuffer::clear() {
        free(data);
        dataSize = 0;
        return *this;
    }

    VertexBuffer& VertexBuffer::bind() {
        int size = 0;
        for (const gl::LayoutElement& i : vbl->list) {
            size += i.count * i.getTypeSize();
        } 
        glBindBuffer(GL_ARRAY_BUFFER, BufferID);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
        int a = 0;
        for (int i = 0; i < vbl->list.size(); i++) {
            glVertexAttribPointer(i , vbl->list[i].count , vbl->list[i].type , (int)vbl->list[i].normalized , size , (const void*)a);
            glEnableVertexAttribArray(i);
            a += vbl->list[i].count * vbl->list[i].getTypeSize();
        }
        return *this;
    }

    VertexBuffer& VertexBuffer::unBind() {
        glBindBuffer(GL_ARRAY_BUFFER,0);
        return *this;
    }   


};