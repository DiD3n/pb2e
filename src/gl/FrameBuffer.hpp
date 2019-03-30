#pragma once

#include "Texture.hpp"
#include "VectorType.hpp"

namespace gl
{

    class FrameBuffer
    {
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

        void clear();

        constexpr const gl::Texture& getAsTexture() const {return *texture;}

        constexpr Vector2ui getSize() const {return size;}
        void setSize(const Vector2ui&);

        void use(bool = true) const;

        operator const gl::Texture()& {return *texture;}
        operator const gl::SubTexture() {return {*texture};}
    };

}; //namespace gl