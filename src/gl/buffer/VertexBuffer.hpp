#pragma once

#include "VertexBufferLayout.hpp"


namespace gl {

    class Renderer;

    class VertexBuffer { //TODO: optimization
    private:

        void* data = nullptr;
        unsigned int dataSize = 0, maxSize = 0;
        
        unsigned int BufferID = 0, VAOID = 0;

        bool legit = true;
        const VertexBufferLayout vbl;

    public:

        VertexBuffer(const VertexBuffer& other);
        VertexBuffer(const VertexBufferLayout& vbl);
        ~VertexBuffer();

        template<typename T, typename ... T2> 
        void push(const T& arg,const T2&... args);
        void reserve(unsigned int size);

        constexpr bool isLegit() const {return legit;}
        constexpr unsigned int getDataCount() const {return dataSize/vbl.stride;}
        constexpr unsigned int getStride() {return vbl.getStride();}

        VertexBuffer& clear();

        void use() const;
        friend Renderer;
    };

};
#include "VertexBuffer.inl"