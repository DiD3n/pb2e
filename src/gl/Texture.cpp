#include "Texture.hpp"

#include "../include/glew.hpp"
#include "../include/sdl2.hpp"
#include "../logger.hpp"

namespace gl {
    Texture::Texture(const std::string& path)
     : path(path) {
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
            SDL_Surface* tmpSurface = NULL;
            tmpSurface = SDL_CreateRGBSurfaceWithFormat(0, surface->w, surface->h, 32, SDL_PIXELFORMAT_RGBA32);
            if (tmpSurface != NULL) {

                for (int x = 0; x < surface->w; x++) {
                    for (int y = 0; y < surface->h; y++) {
                        Uint32 * tmpPixels = (Uint32 *)tmpSurface->pixels;
                        Uint32 * imgPixels = (Uint32 *)surface->pixels;

                        tmpPixels[tmpSurface->w*y + x] = imgPixels[tmpSurface->w*-(y+1-surface->h) + x];
                    }
                }
            } 
            else {
                tmpSurface = surface;
            }
    
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpSurface->pixels );
            SDL_FreeSurface(tmpSurface);
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