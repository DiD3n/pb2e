#pragma once

#include "Texture.hpp"
#include "VectorType.hpp"

namespace gl {

    class FrameBuffer {
        private:
        unsigned int id;
        Vector2i size;
        gl::Texture* texture;
        bool legit;
        
        void setup();
        public:

        FrameBuffer(const Vector2i&);
        FrameBuffer(const FrameBuffer&);
        ~FrameBuffer();

        constexpr const gl::Texture& getAsTexture() const {return *texture;}

        Vector2f getSize() const;
        void setSize(const Vector2f&);

        void use(bool = true) const;
    };

};