#include "Renderer.hpp"

namespace gl {

    template<ubyte type, typename... T>
    void Renderer::draw(const gl::Shader& shader, const gl::SubTexture& texture, const std::array<Vector2f,type>& vert, const T&... args) {

        //looking for matching buffer
        for (int i = 0; i < buffers.size(); i++) {

            if (shader == *(buffers[i].shader)) { //checking shader

                if (texture.texture == *(buffers[i].texture)) { //checking texture

                    /* filling Buffer */

                    if (sizeof(float) * 4 + sizeOfMulti(args...) == buffers[i].buffer.getStride()) {

                        buffers[i].buffer.reserve(type);

                        for (char j = 0; j < type; j++) 
                            buffers[i].buffer.push(vert[j],texture.uv.getVertices()[j],args...);

                    } else 
                    if (buffers[i].basic) {

                        buffers[i].buffer.reserve(type);

                        for (char j = 0; j < type; j++) 
                            buffers[i].buffer.push(vert[j],texture.uv.getVertices()[j]);

                    } 
                    else
                        continue;


                    /* filling IBO */

                    if (type == gl::rectangle) {

                        buffers[i].ibo.reserve(6);
                        unsigned char iboTemplate[6] = { 0,1,2,0,3,2 };
                        for (int j = 0; j < 6; j++)
                            buffers[i].ibo.emplace_back((buffers[i].buffer.getDataCount()-type)+iboTemplate[j]);

                    } 
                    else {

                        buffers[i].ibo.reserve(type);
                        int size = buffers[i].buffer.getDataCount() - type; 
                        for (int j = size; j < size+type; j++)
                            buffers[i].ibo.emplace_back(j);

                    }

                    return;

                }

            }

        }

        /* creating a naw one buffer */

        logWarn("gl::Renderer::draw(t) - No matching buffer found... Creating new one!");
        if (sizeOfMulti(args...) != 0)
            logWarn("gl::Renderer::draw(t) - All arguments will be lost!");


		gl::VertexBufferLayout layout;
		layout.push({2}).push({2});

		buffers.emplace_back(layout,texture.texture,shader);
        buffers.back().basic = true;

        draw<type>(shader,texture,vert,args...);

		return;
    }

    template<ubyte type, typename... T>
    void Renderer::draw(const gl::Shader& shader, const std::array<Vector2f,type>& vert, const T&... args) {

        //looking for matching buffer
        for (int i = 0; i < buffers.size(); i++) {

            if (nullptr == buffers[i].texture) { //checking buffer 

                if (shader == *(buffers[i].shader)) { //checking shader
                       
                    /* filling Buffer */

                    if (sizeof(float) * 2 + sizeOfMulti(args...) == buffers[i].buffer.getStride()) {

                        buffers[i].buffer.reserve(type);

                        for (char j = 0; j < type; j++) 
                            buffers[i].buffer.push(vert[j],args...);

                    } else 
                    if (buffers[i].basic) {

                        buffers[i].buffer.reserve(type);

                        for (char j = 0; j < type; j++) 
                            buffers[i].buffer.push(vert[j]);

                    }
                    else
                        continue;


                    /* filling IBO */

                    if (type == gl::rectangle) {

                        buffers[i].ibo.reserve(6);
                        unsigned char iboTemplate[6] = { 0,1,2,0,3,2 };
                        for (int j = 0; j < 6; j++)
                            buffers[i].ibo.emplace_back(buffers[i].buffer.getDataCount()-type+iboTemplate[j]);

                    } 
                    else {

                        buffers[i].ibo.reserve(type);
                        int size = buffers[i].buffer.getDataCount()-type; 
                        for (int j = size; j < size+type; j++)
                            buffers[i].ibo.emplace_back(j);

                    }

                    return;

                }

            }

        }

        /* creating a naw one buffer */

        logWarn("gl::Renderer::draw(nt) - No matching buffer found... Creating new one!");
        if (sizeOfMulti(args...) != 0)
            logWarn("gl::Renderer::draw(nt) - All arguments will be lost!");


		gl::VertexBufferLayout layout;
		layout.push({2});

		buffers.emplace_back(layout,shader);
        buffers.back().basic = true;

        draw<type>(shader,vert);

		return;
    }

};