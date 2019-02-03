#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#define _DEBUG

#include "logger.hpp"
#include "include/glew.hpp"
#include "include/glm.hpp"

#include "gl/VertexBufferLayout.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/Shader.hpp"
#include "gl/Texture.hpp"
#include "gl/VectorType.hpp"
#include "gl/RectType.hpp"
#include "gl/Renderer.hpp"
#include "gl/FrameBuffer.hpp"

#include "system/memory.hpp"

typedef unsigned char uchar;

int main(int argc, char *argv[]) {
    int exitCode = EXIT_SUCCESS;
    SDL_Window* window = NULL;

    showLogo();
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        logError("SDL_Init");
        exitCode = EXIT_FAILURE;
        goto main_exit;
    } else {
        int flags = IMG_INIT_PNG;
        if (!( IMG_Init( flags ) & flags )) {
            logError("IMG_Init");
            exitCode = EXIT_FAILURE;
            goto main_exit;
        }
    }
    window = SDL_CreateWindow("pb2e - openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        logError("SDL_CreateWindow");
    } else {
        SDL_GLContext context = nullptr;
        context = SDL_GL_CreateContext(window);
        if (!context) {
           logError("SDL_GL_CreateContext");
        } else {
            unsigned int initErr = glewInit();
            if (initErr != GLEW_OK) {
                logError("glewInit");
            } else {
                if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
					logError("Vsync problem!");
				}
                logInfo("Init - done!");
                gl::Renderer renderer;
                gl::Texture texture("res/weed.png", gl::nearest);
                gl::Shader shader("res/basicVertex.glsl","res/basicFragment.glsl");
                gl::Shader shader2("res/basicUIVert.glsl","res/basicUIFrag.glsl");
                gl::FrameBuffer frameBuffer({800,600});

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glm::mat4 mvp = glm::ortho(-400.0f,400.0f,-300.0f,300.0f,-1.0f,1.0f);
                
                {
                    gl::Uniform un(true,mvp);
                    shader.pushUniform("MVP",un);
                    shader.update();
                    shader2.pushUniform("MVP",un);
                    shader2.update();

                    gl::VertexBufferLayout layout;
                    layout << gl::LayoutElement(2) << gl::LayoutElement(2) << gl::LayoutElement(3,GL_UNSIGNED_BYTE,true);
                    renderer.pushCustomBuffer(layout,frameBuffer.getAsTexture(),shader);
                    renderer.pushCustomBuffer(layout,texture,shader);

                    gl::VertexBufferLayout layout2;
                    layout2.push({2}).push(4,GL_UNSIGNED_BYTE,true);
                    renderer.pushCustomBuffer(layout2,shader2);
                    
                }
                gl::VertexBufferLayout layout;
                layout << gl::LayoutElement(2) << gl::LayoutElement(2) << gl::LayoutElement(3,GL_UNSIGNED_BYTE,true);



                gl::VertexBuffer myBuffer(layout);
                
                
                    gl::Rectf rect(-400.f,-400.f,800.f,800.f);
                    gl::SubTexture st(texture,{0.f, 0.f, 1.f, 1.f});
                    myBuffer.use();
                    for (int i = 0; i < 4; i++) {
                        myBuffer.push(rect.getVertices()[i], st.uv.getVertices()[i],(uchar)128,(uchar)255,(uchar)0);
                    }
                   
                gl::Rectf weedSize(-400.f,-300.f,800.f,600.f);      
                gl::Rectf rectt(-50.f,-50.f,300.f,300.f);
 
                while(unsigned int err = glGetError()) {
                    std::cout << err << "\n";
                }

                unsigned int frame = 0;
                bool end = false;
                while (!end) {
                    
                    SDL_Event ev;
                    while (SDL_PollEvent(&ev)) {
                        switch (ev.type) {
                            case SDL_QUIT: //exit
                                end = true;
                            break;

                            case SDL_WINDOWEVENT: //resize
                                switch (ev.window.event) {
                                case SDL_WINDOWEVENT_SIZE_CHANGED:
                                    int w = ev.window.data1, h = ev.window.data2;
                                    glViewport(0, 0, w, h);
                                    mvp = glm::ortho(-(float)w/2,(float)w/2,-(float)h/2,(float)h/2,-1.0f,1.0f);
                                    shader.update("MVP");
                                    shader2.update("MVP");
                                    break;
                                }
                            break;

                            case SDL_MOUSEWHEEL:
                            float c;
                            if(ev.wheel.y > 0)
                                c = weedSize.h* 1.1f - weedSize.h;
                            else if(ev.wheel.y < 0)
                                c = weedSize.h* 0.9f - weedSize.h;
                            weedSize.h += c;
                            weedSize.w += c;
                            weedSize.x -= c/2;
                            weedSize.y -= c/2;
                            break;

                            case SDL_KEYUP: //recompile
                                if (ev.key.keysym.sym == SDLK_r)
                                    shader.recompile();
                        }
                    }
                    glClear(GL_COLOR_BUFFER_BIT);

                    renderer.clear();
                    frameBuffer.clear();
                    {   //render to frameBuffer

                        renderer.draw<gl::rectangle>(shader,texture,weedSize,(uchar)32,(uchar)255,(uchar)255);
                        renderer.draw<gl::rectangle>(shader,texture,rectt,(uchar)255,(uchar)255,(uchar)0);

                        std::array<gl::Vector2f,3> arr={gl::Vector2f(-500,500),gl::Vector2f(-500,-500),gl::Vector2f(500,-500)};
                        renderer.draw<3>(shader,texture,arr,1.f,1.f);

                    }
                    renderer.finalRender();
                    frameBuffer.use(false);
                    renderer.clear();
                    {   //render to screen

                        renderer.draw<gl::rectangle>(shader,frameBuffer.getAsTexture(),rectt,(uchar)255,(uchar)255,(uchar)255);
                        renderer.draw<gl::rectangle>(shader2,weedSize,(uchar)255,(uchar)32,(uchar)255,(ubyte)128);

                    }
                    renderer.finalRender();

                    SDL_GL_SwapWindow( window );
                    frame++;
                    while (unsigned int err = glGetError())
                        logError(err);
                }
            }
        }
        SDL_GL_DeleteContext(context);
    }
    SDL_DestroyWindow(window);
    main_exit:
    if (exitCode)
        std::cin.get();
    return exitCode;
}