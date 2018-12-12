#include "Texture.hpp"

#include "../include/glew.hpp"
#include "../include/sdl2.hpp"
#include "../logger.hpp"

namespace gl {
    Texture::Texture(const std::string& path)
     : path(path){
        glGenTextures(1,&id);
        legit = this->load();
    }
    Texture::Texture(const Texture& other) {
        Texture(other.path);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->id);
    }

    bool Texture::load() {
        bool done = false;
        SDL_Surface* surface = NULL;

        surface = IMG_Load(this->path.c_str());
        if (surface == NULL) {
            logError("gl::Texture::load(",path,") - IMG_Load");
        } 
        else {
            this->bind();
    
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );
        }   

        SDL_FreeSurface(surface);
        return done;
    }

    bool Texture::reload() {
        return true;
    }

    inline void Texture::bind()   const {glBindTexture(GL_TEXTURE_2D,id);};
    inline void Texture::unBind() const {glBindTexture(GL_TEXTURE_2D, 0);};
};