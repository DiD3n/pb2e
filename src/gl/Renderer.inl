#include "Renderer.hpp"

struct _dummy {};

namespace gl {
    template<ubyte type, typename T, typename... T2 >
    void Renderer::draw(const gl::Shader& shader, const gl::SubTexture& texture,std::array<Vector2f,type> vector, const T& arg, const T2&... args) {

        unsigned int argsSize = sizeOfMulti(arg, args...);

        for (BufferDB& i : buffers) {
                
           if (i.texture == texture.texture && i.shader == shader) {
                if (i.buffer.vbl.getStride() - (4*sizeof(float)) == argsSize) {

                    unsigned int lastVert = i.buffer.getDataCount();
                    switch (type) {
                        case rectangle:
                        {
                            unsigned char ibo[6] = { 0,1,2,0,3,2 };
                            i.ibo.reserve(6);
                            for (int j = 0;j <  6; j++)
                                i.ibo.emplace_back(ibo[j] + lastVert);
                        }
                        break;
                        default:
                        {
                            i.ibo.reserve(type);
                            for (int j = 0;j < type; j++)
                            i.ibo.emplace_back(j + lastVert);   
                        }
                        
                        break;
                    }

                    for (int j = 0; j < type; j++)
                        i.buffer.push(vector[j], texture.uv.getVertices()[j], arg, args...);

                    return;
                }
            }    
        }
        
        logInfo("Renderer::render() - no matching buffer found... creating a new one");
        if (argsSize < 0)
            logInfo("Renderer::render() - all arguments will be abandoned",'\n', cppToString(args...));

        gl::VertexBufferLayout layout;
        layout << gl::LayoutElement(2) << gl::LayoutElement(2);
        buffers.emplace_back(layout, texture.texture, shader);
        this->draw<type>(shader,texture,vector,arg,args...);

    }

    template<ubyte type>
    void Renderer::draw(const gl::Shader& shader, const gl::SubTexture& texture, std::array<Vector2f,type> vector) {
        _dummy dummy;
        this->draw<type>(shader,texture,vector,dummy);
    }
};