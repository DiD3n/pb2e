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

                gl::Renderer renderer;
                gl::Texture texture("res/weed.png");
                gl::Shader shader("res/basicVertex.glsl","res/basicFragment.glsl");

                glm::mat4 mvp = glm::ortho(-400.0f,400.0f,-300.0f,300.0f,-1.0f,1.0f);
                
                {
                    gl::Uniform un(true,mvp);
                    shader.pushUniform("MVP",un);
                    shader.update();

                    gl::VertexBufferLayout layout;
                    layout << gl::LayoutElement(2) << gl::LayoutElement(2) << gl::LayoutElement(3,GL_UNSIGNED_BYTE,true);
                    renderer.pushCustomLayout(layout,texture,shader);
                }
                

                gl::Rectf weedSize(-128.f,-128.f,256.f,256.f);      
                gl::Rectf rectt(-100.f,-100.f,300.f,300.f);

                while(unsigned int err = glGetError()) {
                    std::cout << err << "\n";
                }
                unsigned int frame = 0;
                bool end = false;
                unsigned int memo;

                auto lastTime = std::chrono::high_resolution_clock::now();
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
                    
                    renderer.draw<gl::rectangle>(shader,texture,rectt,(uchar)255,(uchar)0,(uchar)255);
                    renderer.draw<gl::rectangle>(shader,texture,weedSize,(uchar)255,(uchar)255,(uchar)0);
                    
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