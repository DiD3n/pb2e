#include "Uniform.hpp"

#include "../logger.hpp"

namespace gl {

    Uniform::~Uniform() {
        if (!pointable) 
            free(data);
    }

    Uniform& Uniform::operator=(const Uniform& other) {
        if (other.pointable) {
            this->data = other.data;
        }
        this->pointable = other.pointable;
        return *this;
    }
    
}

