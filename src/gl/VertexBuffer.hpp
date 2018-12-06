#pragma once

#include "VertexBufferLayout.hpp"

#include "../logger.hpp"
#include "../include/glew.hpp"

template<typename T> 
unsigned int sizeOfMulti(const T& arg) { return sizeof(arg);}

template<typename T, typename ... T2> 
unsigned int sizeOfMulti(const T& arg,const T2&... args) { return sizeOfMulti(args...) + sizeof(arg); }



template<typename T> 
void pushData(void* data, const T& arg) {
    memcpy(data, &arg, sizeof(arg));
}

template<typename T, typename ... T2> 
void pushData(void* data, const T& arg,const T2&... args) {
    memcpy(data, &arg, sizeof(arg));
    pushData((char*)data + sizeof(arg), args...);
}

namespace gl {

    class VertexBuffer {
        private:
        void* data = nullptr;
        unsigned int dataSize = 0;
        unsigned int BufferID = 0;
        bool legit = true;
        VertexBufferLayout* vbl;

        public:
        VertexBuffer(VertexBufferLayout& vbl, bool ref = false);
        ~VertexBuffer();

        template<typename T, typename ... T2> 
        void push(const T& arg,const T2&... args) {
            if (vbl->stride == sizeOfMulti(arg,args...)) {
                data = (void*)realloc((void*)data, dataSize + vbl->stride);
                pushData((char*)data + dataSize, arg, args...);
                dataSize += vbl->stride;
            } else {
                logError("gl::VertexBuffer::push()","- data size(",sizeOfMulti(arg,args...),") isn't equal stride(",vbl->stride,")... skipping");
            }
        }

        constexpr bool isLegit() {return legit;}
        constexpr unsigned int getDataCount() {return dataSize/vbl->stride;}

        VertexBuffer& clear();

        VertexBuffer& bind();
        VertexBuffer& unBind();
    };

};