#include "Renderer.hpp"

namespace gl {

    void Renderer::pushCustomLayout(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader) {
        buffers.emplace_back(layout, texture.texture, shader);
    }

    void Renderer::finalRender() {
        for (BufferDB& i : buffers) {

            i.buffer.use();
            i.shader.bind();
            i.texture.bind();

            GLCall(glDrawElements(GL_TRIANGLES,i.ibo.size(),GL_UNSIGNED_INT, (void*)&(i.ibo[0])));

        }
    }

    void Renderer::clear() {
        for (BufferDB& i : buffers) {

            i.ibo.clear();
            i.buffer.clear();
            
        }
    }

};