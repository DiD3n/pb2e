#include "FrameBuffer.hpp"

#include "../logger.hpp"
#include "../include/glew.hpp"

namespace gl {

    FrameBuffer::FrameBuffer(const Vector2ui& size)
     : size(size) , texture(nullptr) , legit(true) {
        GLCall(glGenFramebuffers(1,&id));
        setup();
    }
    FrameBuffer::FrameBuffer(const FrameBuffer& other)
     : size(other.size) , texture(nullptr) , legit(true) {
        GLCall(glGenFramebuffers(1,&id));
        setup();
    }
    FrameBuffer::~FrameBuffer() {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        GLCall(glDeleteFramebuffers(1,&id));
        if (texture != nullptr)
            delete texture;
    }

    void FrameBuffer::setup() {
        if (texture != nullptr)
            delete texture;
        
        texture = new gl::Texture(size, gl::nearest);
        
        use();
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
        GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0));

        GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBuffers);

        auto err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        legit = (err == GL_FRAMEBUFFER_COMPLETE);

        use(false);

        if (!legit) {
            logInfo("FrameBuffer::setup() - Somthing gone wrong!");
            switch (err) {
                case GL_FRAMEBUFFER_UNSUPPORTED:                      logInfo("FrameBuffer::setup() - GL_FRAMEBUFFER_UNSUPPORTED");
                return;
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:            logInfo("FrameBuffer::setup() - GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
                return;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:    logInfo("FrameBuffer::setup() - GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
                return;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:           logInfo("FrameBuffer::setup() - GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");  
                return;
                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:         logInfo("FrameBuffer::setup() - GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");  
                return;
            }
        }
    }

    void FrameBuffer::clear() {
        use();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void FrameBuffer::setSize(const Vector2ui& size) {
        this->size = size;
        texture->setSize(size);
    }

    void FrameBuffer::use(bool bind) const {
        static unsigned int lastID;
        if (legit) {
            if (bind) {
                if (lastID != id) {
                    lastID = id;
                    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
                }
                return;
            }
        }
            
        if (lastID != 0) {
            lastID = 0;
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }
    }

};