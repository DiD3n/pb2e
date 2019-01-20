#include "Texture.hpp"

#include "../include/glew.hpp"
#include "../include/sdl2.hpp"
#include "../logger.hpp"
#include "../include/glm.hpp"

namespace gl {

    /* SubTexture */

    void SubTexture::genUV(const gl::Rectui& rect, bool isWHpos2) {
        uv.x = (float)rect.x / texture.getSize().x;
        uv.y = (float)rect.y / texture.getSize().y;
        if (isWHpos2) {
            uv.w = (float)rect.w / texture.getSize().x;
            uv.h = (float)rect.h / texture.getSize().y;
            return;
        }
        uv.w = (float)rect.w + (float)rect.x / texture.getSize().x;
        uv.h = (float)rect.h + (float)rect.y / texture.getSize().y;
    }

    /* Texture */

    Texture::Texture(const std::string& path, const TextureFiltering& filter)
     : path(path) , filter(filter) {
        GLCall(glGenTextures(1,&id));
        legit = this->load();
    }
    Texture::Texture(const Vector2ui& size, const TextureFiltering& filter)
     : path("") , filter(filter) , w(size.x) , h(size.y) {
        GLCall(glGenTextures(1,&id));
        use();

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)); 
	    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, size.x, size.y, 0,GL_RGB, GL_UNSIGNED_BYTE, 0));
        use(false);
        legit = true;
    }
    Texture::Texture(const Texture& other)
     : path(path) , filter(filter) {
        GLCall(glGenTextures(1,&id)); 
        logInfo("Texture::Texture(const Texture&) - is not coping the texture!");
    }

    Texture::~Texture() {
        GLCall(glDeleteTextures(1, &this->id));
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
            use();
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
            
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpSurface->pixels));
            this->w = surface->w;
            this->h = surface->h;
            SDL_FreeSurface(tmpSurface);
            done = true;
        }

        SDL_FreeSurface(surface);
        return done;
    }

    bool Texture::reload() { //TODO: Dynamic reload
        return true;
    }

    void Texture::setSize(const Vector2ui& size) {
        use();
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, size.x, size.y, 0,GL_RGB, GL_UNSIGNED_BYTE, 0));
        w = size.x;
        h = size.y;
    }

    void Texture::use(bool bind) const {
        static unsigned int lastID;
        if (legit) {
            if (bind) {
                if (lastID != id) {
                    lastID = id;
                    GLCall(glBindTexture(GL_TEXTURE_2D,id));
                }
                return;
            }
        }

        if (lastID != 0) {
            lastID = 0;
            GLCall(glBindTexture(GL_TEXTURE_2D,0));
        }
    }
};