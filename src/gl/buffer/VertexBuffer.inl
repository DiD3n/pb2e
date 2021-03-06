#include "VertexBuffer.hpp"

#include "../../logger.hpp"
#include "../../include/glew.hpp"

constexpr unsigned int sizeOfMulti()
{
    return 0;
}

template<typename T, typename ... T2>
unsigned int sizeOfMulti(const T& arg,const T2&... args)
{
    return sizeOfMulti(args...) + sizeof(arg);
}


template<typename T>
void pushData(void* data, const T& arg)
{
    memcpy(data, &arg, sizeof(arg));
}

template<typename T, typename ... T2>
void pushData(void* data, const T& arg,const T2&... args)
{
    memcpy(data, &arg, sizeof(arg));
    pushData((char*)data + sizeof(arg), args...);
}


namespace gl {

    template<typename T, typename ... T2>
    void VertexBuffer::push(const T& arg, const T2&... args) {

        if (vbl.stride == sizeOfMulti(arg,args...))
        {
            if (maxSize - dataSize < vbl.stride )
            {
                data = (void*)realloc((void*)data, dataSize + vbl.stride);
                maxSize  += vbl.stride;
            } 

            pushData((char*)data + dataSize, arg, args...);
            dataSize += vbl.stride;

        }
        else 
        {
            logError("gl::VertexBuffer::push()","- data size(",sizeOfMulti(arg,args...),") isn't equal stride(",vbl.stride,")... skipping");
        }
    }

};
