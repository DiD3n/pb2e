#pragma once

#include <string>
#include "RectType.hpp"

#define GL_TEXTURE_2D 0x0DE1


namespace gl {

    class Texture;

    class SubTexture {
        public:
        const Texture& texture;
        Rectf uv;
        SubTexture(const SubTexture& other)
         : texture(other.texture) , uv(other.uv) {}
        SubTexture(const Texture& texture)
         : texture(texture) {}
         SubTexture(const Texture& texture, const Rectf& uv)
         : texture(texture) , uv(uv) {}
        void genUV(const gl::Rectui& rect, bool isWHpos2 = false);
    };

    class Texture {
    private:
        unsigned int id;
        unsigned int w, h;
        const std::string path;
        bool legit;

        bool load();

    public:
        Texture(const std::string& path);
        Texture(const Texture& other);
        ~Texture();

        bool reload();

        constexpr bool isLegit() const {return legit;}
        Vector2ui getSize() const {return {w,h};}

        inline void bind() const;
        inline void unBind() const;


        operator SubTexture() {
            return { *this, {0.f, 0.f, 1.f, 1.f} };
        }    
    };
    
};
