#include "Renderer.hpp"

namespace gl {

    void Renderer::pushCustomBuffer(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader) {
        buffers.emplace_back(layout, texture.texture, shader);
    }
    void Renderer::pushCustomBuffer(const VertexBufferLayout& layout, const Shader& shader) {
        buffers.emplace_back(layout, shader);
    }

    void Renderer::finalRender() {
        for (BufferDB& i : buffers) {

            i.buffer.use();
            i.shader->use();

            if (i.texture) //if not NULL
                i.texture->use();

            GLCall(glDrawElements(GL_TRIANGLES,i.ibo.size(), GL_UNSIGNED_INT, (void*)&(i.ibo[0])));

        }
    }

    void Renderer::clear() {
        for (BufferDB& i : buffers) {

            i.ibo.clear();
            i.buffer.clear();
            
        }
    }

    bool Renderer::checkBufferExists(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader) {
        for (BufferDB& i : buffers) {
            if (!i.texture)
                continue;
            if (i.buffer.vbl == layout && *(i.texture) == texture.texture && *(i.shader) == shader)
                return true;
        }
        return false;
    }

    bool Renderer::checkBufferExists(const VertexBufferLayout& layout, const Shader& shader) {
        for (BufferDB& i : buffers) {
            if (i.buffer.vbl == layout && *(i.shader) == shader)
                return true;
        }
        return false;
    }

};