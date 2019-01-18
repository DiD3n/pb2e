#pragma once

#include <string>
#include "RectType.hpp"
#include "VectorType.hpp"

#define GL_TEXTURE_2D 0x0DE1
#define GL_LINEAR 0x2601
#define GL_NEAREST 0x2600

namespace gl {

    enum TextureFiltering {
        linear = GL_LINEAR,
        nearest = GL_NEAREST
    };

    class Texture;
    class SubTexture {
        public:
        const Texture& texture;
        Rectf uv;
        SubTexture(const SubTexture& other)
         : texture(other.texture) , uv(other.uv) {}
        SubTexture(const Texture& texture)
         : texture(texture) , uv(0.f, 0.f, 1.f, 1.f) {}
         SubTexture(const Texture& texture, const Rectf& uv)
         : texture(texture) , uv(uv) {}
        void genUV(const gl::Rectui& rect, bool isWHpos2 = false);
    };

    class FrameBuffer;
    class Texture {
    private:
        unsigned int id;
        unsigned int w, h;
        const std::string path;
        const TextureFiltering filter;
        bool legit;

        bool load();

    public:
        Texture(const Vector2i& size, const TextureFiltering& = linear);
        Texture(const std::string& path, const TextureFiltering& = nearest);
        Texture(const Texture& other);
        ~Texture();

        constexpr bool operator==(const Texture& other) const {return (id == other.id);}

        bool reload();

        constexpr bool isLegit() const {return legit;}
        constexpr Vector2ui getSize() const {return {w,h};}

        void bind() const;
        void unBind() const;


        operator SubTexture() {
            return { *this, {0.f, 0.f, 1.f, 1.f} };
        }    
        friend FrameBuffer;
    };
    
};
