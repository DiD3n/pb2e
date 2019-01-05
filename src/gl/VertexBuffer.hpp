#pragma once

#include "VertexBufferLayout.hpp"
#include "RectType.hpp"

#include "../logger.hpp"
#include "../include/glew.hpp"


namespace gl {

    class Renderer;

    class VertexBuffer {
        private:
        void* data = nullptr;
        unsigned int dataSize = 0;
        unsigned int BufferID = 0, VAOID = 0;
        bool legit = true;
        VertexBufferLayout vbl;

        public:
        VertexBuffer(const VertexBuffer& other); //TODO: Copy constructor
        VertexBuffer(const VertexBufferLayout& vbl);
        ~VertexBuffer();

        template<typename T, typename ... T2> 
        void push(const T& arg,const T2&... args);

        constexpr bool isLegit() const {return legit;}
        constexpr unsigned int getDataCount() const {return dataSize/vbl.stride;}

        VertexBuffer& clear();

        void bind() const;
        void unBind() const;
        friend Renderer;
    };

};
#include "VertexBuffer.inl"