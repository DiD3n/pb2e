#pragma once

#include <string>
#include "RectType.hpp"

#define GL_TEXTURE_2D 0x0DE1


namespace gl {

    class Texture;

    class subTexture {
        public:
        const Texture& texture;
        Rectf uv;
        subTexture(const Texture& texture)
         : texture(texture) {}
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

    };
    
};
