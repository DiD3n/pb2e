#include "VertexBuffer.hpp"



namespace gl {

    VertexBuffer::VertexBuffer(const VertexBuffer& other) {
        VertexBuffer(other.vbl);
    }

    VertexBuffer::VertexBuffer(const VertexBufferLayout& vbl) : vbl(vbl) {

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

    void VertexBuffer::bind() const{
        GLCall(glBindVertexArray(VAOID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW));
    }

    void VertexBuffer::unBind() const{
        GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
    }   


};