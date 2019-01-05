#pragma once 

#include <string>
#include <vector>
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
        BufferDB(const BufferDB& other)
         : buffer(other.buffer) , texture(other.texture) , shader(other.shader) {}
        BufferDB(const VertexBufferLayout& layout, const Texture& texture, const Shader& shader)
         : buffer(layout) , texture(texture) , shader(shader) {}
    };

    

    class Renderer {
        std::vector<BufferDB> buffers;
        public:

        void pushCustomLayout(const VertexBufferLayout& layout, const SubTexture& texture, const Shader& shader);

        void finalRender();

        void clear();
        
        template<ubyte type, typename T, typename... T2 >
        void draw(const gl::Shader& shader, const gl::SubTexture& texture, std::array<Vector2f,type> vector, const T& arg, const T2&... args);

        template<ubyte type>
        void draw(const gl::Shader& shader, const gl::SubTexture& texture, std::array<Vector2f,type> vector);

        //void renderCustom();

    };

};

#include "Renderer.inl"