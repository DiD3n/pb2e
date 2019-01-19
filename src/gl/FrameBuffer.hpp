#pragma once

#include "Texture.hpp"
#include "VectorType.hpp"

namespace gl {

    class FrameBuffer {
        private:
        unsigned int id;
        Vector2ui size;
        gl::Texture* texture;
        bool legit;
        
        void setup();
        public:

        FrameBuffer(const Vector2ui&);
        FrameBuffer(const FrameBuffer&);
        ~FrameBuffer();

        constexpr const gl::Texture& getAsTexture() const {return *texture;}

        constexpr Vector2ui getSize() const {return size;}
        void setSize(const Vector2f&);

        void use(bool = true) const;
    };

};