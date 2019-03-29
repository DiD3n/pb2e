#include "Uniform.hpp"

#include <typeinfo>
#include "../../logger.hpp"
#include "../../include/glm.hpp"

template<typename T>
static void pushDataArray(T* data, const T& arg)
{
    data[0] = arg; 
}

template<typename T, typename ... T2>
static void pushDataArray(T* data, const T& arg, const T2&... args)
{
    data[0] = arg;
    pushDataArray(data + 1, args...);
}

namespace gl
{

    
    template<typename T, typename ... T2>
    Uniform::Uniform(const T& arg, const T2&... args)
     : pointable(false) , size(sizeOfMulti(arg,args...))
     {
            
        int dataCount = size/sizeof(T);
             if (typeid(T) == typeid(float))        this->type = (UniformType)(10 * dataCount + 0);
        else if (typeid(T) == typeid(unsigned int)) this->type = (UniformType)(10 * dataCount + 1);
        else if (typeid(T) == typeid(int))          this->type = (UniformType)(10 * dataCount + 2);
		else if (typeid(T) == typeid(double))     	this->type = (UniformType)(10 * dataCount + 3);

        data = (T*)malloc(size);
        
        pushDataArray((T*)data,arg,args...);
    }

    template<typename T>
    Uniform::Uniform(bool pointable, T& arg)
    : pointable(pointable) , size(sizeof(size))
    {

             if (typeid(T) == typeid(float))        this->type = vec1f; 
        else if (typeid(T) == typeid(int))          this->type = vec1i; 
        else if (typeid(T) == typeid(unsigned int)) this->type = vec1ui;
		else if (typeid(T) == typeid(double)) 		this->type = vec1d;
        else if (typeid(T) == typeid(glm::mat2))    this->type = mat2;
        else if (typeid(T) == typeid(glm::mat3))    this->type = mat3;
        else if (typeid(T) == typeid(glm::mat4))    this->type = mat4;
        
        if (pointable)
        {
            data = &arg;
        }   
        else
        {
            data = malloc(sizeof(T));
            pushDataArray((T*)data,arg);
        } 
    }

}; //namespace gl