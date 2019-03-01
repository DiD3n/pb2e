#pragma once 

#include <string>
#include <vector>
#include <list>
#include <array>

#include "buffer/VertexBuffer.hpp"
#include "Texture.hpp"
#include "shader/Shader.hpp"
#include "ColorType.hpp"


namespace gl {

    enum Shape : unsigned char {
        none      = 0,
        point     = 1,
        line      = 2,
        triangle  = 3,
        rectangle = 4 
        //TODO: Add circle??
    };

    struct BufferDB {
        VertexBuffer buffer;
        const Texture* const texture;
        const Shader* const shader;
        std::vector<unsigned int> ibo;
        bool basic;
        BufferDB(const BufferDB& other)
         : buffer(other.buffer) , texture(other.texture) , shader(other.shader) , basic(other.basic) , ibo(other.ibo) {}
        BufferDB(const VertexBufferLayout& layout, const Texture& texture, const Shader& shader)
         : buffer(layout) , texture(&texture) , shader(&shader) , basic(false) {}
         BufferDB(const VertexBufferLayout& layout, const Shader& shader)
         : buffer(layout) , texture(nullptr) , shader(&shader) , basic(false) {}
    };

    class Renderer {
    private:
        std::vector<BufferDB> buffers;

    public:
        /* <3 */

        template<ubyte type, typename... T>
        void draw(const gl::Shader& shader, const gl::SubTexture& texture, const std::array<Vector2f,type>& vert, const T&... args);

        template<ubyte type, typename... T> //without texture
        void draw(const gl::Shader& shader, const std::array<Vector2f,type>& vert, const T&... args);

        void finalRender();

        /* Buffer's stuff */

        void pushCustomBuffer(const VertexBufferLayout&, const SubTexture&, const Shader&);
        void pushCustomBuffer(const VertexBufferLayout&, const Shader&);

        bool checkBufferExists(const VertexBufferLayout&, const SubTexture&, const Shader&);
        bool checkBufferExists(const VertexBufferLayout&, const Shader&);

        void clear();

    };

};

#include "Renderer.inl"