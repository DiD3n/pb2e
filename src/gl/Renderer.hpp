#pragma once 

#include <string>
#include <vector>
#include <list>
#include <array>

#include "VertexBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
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
        const Texture& texture;
        const Shader& shader;
        std::vector<unsigned int> ibo;
        bool basic;
        BufferDB(const BufferDB& other)
         : buffer(other.buffer) , texture(other.texture) , shader(other.shader) , basic(other.basic) {}
        BufferDB(const VertexBufferLayout& layout, const Texture& texture, const Shader& shader)
         : buffer(layout) , texture(texture) , shader(shader) , basic(false) {}
    };

    class Renderer {
    private:
        std::vector<BufferDB> buffers;

    public:

        template<ubyte type, typename... T>
        void draw(const gl::Shader& shader, const gl::SubTexture& texture, const std::array<Vector2f,type>& vert, const T&... args);

        void pushCustomBuffer(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader);

        void finalRender();

        bool checkBufferExists(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader);

        void clear();

        //void renderCustom();

    };

};

#include "Renderer.inl"