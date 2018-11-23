#pragma once

#include "VertexBufferLayout.hpp"

#include "../logger.hpp"
#include "../include/glew.hpp"

template<typename T> 
static constexpr unsigned int sizeOfMulti(const T& arg) {
    return sizeof(arg);
}

template<typename T, typename ... T2> 
static constexpr unsigned int sizeOfMulti(const T& arg,const T2&... args) {
    return sizeOfMulti(args...) + sizeof(arg);
}



template<typename T> 
static constexpr void pushData(void* data, unsigned int byte, const T& arg) {
    memcpy((data)+byte,&arg,sizeof(arg));
}

template<typename T, typename ... T2> 
static constexpr void pushData(void* data, unsigned int byte, const T& arg,const T2&... args) {//static_cast<void*>
    memcpy((data)+byte,&arg,sizeof(arg));
    pushData(data,byte + sizeof(arg), args...);
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
                pushData(data,dataSize,arg,args...);
                dataSize += vbl->stride;
            } else {
                logError("gl::VertexBuffer::push()","- data size(",sizeOfMulti(arg,args...),") isn't equal stride(",vbl->stride,")... skipping");
            }
        }

        constexpr bool isLegit() {return legit;}

        VertexBuffer& clear();

        VertexBuffer& bind();
        VertexBuffer& unBind();
    };

};

//int mm() {
//    gl::VertexBufferLayout vbf;
//    vbf << gl::LayoutElement(2) << gl::LayoutElement(3 ,GL_UNSIGNED_BYTE, true);
//    
//    gl::VertexBuffer buffer(vbf);
//    buffer.push(0.5,0.1,0.0,0.0,0.9).push(0.1,0.1,0.7,0.9,0.0);
//}
//
//
//