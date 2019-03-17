#include "Uniform.hpp"

#include "../../logger.hpp"

namespace gl
{

    Uniform::Uniform(const Uniform& other)
     : pointable(other.pointable) , type(other.type) , size(other.size)
    {

        if (pointable)
        {
            data = other.data;
        }
        else
        {
            data = (void*)realloc((void*)data, size);
            memcpy(data, other.data, size);
        }
        
    }

    Uniform::~Uniform()
    {
        if (!pointable) 
            free(data);
    }
    
} //namespace gl

