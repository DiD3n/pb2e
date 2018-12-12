#pragma once

#include <string>

#define GL_TEXTURE_2D 0x0DE1


namespace gl {

    class Texture {
    private:
        unsigned int id;
        const std::string path;
        bool legit;

        bool load();

    public:
        Texture(const std::string& path);
        Texture(const Texture& other);
        ~Texture();

        bool reload();

        constexpr bool isLegit() const {return legit;}

        inline void bind()   const;
        inline void unBind() const;

    };
    
};
