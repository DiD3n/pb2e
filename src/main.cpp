#include <iostream>
#include <string>
#include <fstream>

#define _DEBUG

#include "logger.hpp"
#include "include/glew.hpp"
#include "include/glm.hpp"

#include "gl/VertexBufferLayout.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/Shader.hpp"
#include "gl/Texture.hpp"

#include "misc/memory.hpp"

typedef unsigned char uchar;

int main(int argc, char *argv[]) {
    logInfo(getMemoryUsage(), "- start");
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
    logInfo(getMemoryUsage());
    window = SDL_CreateWindow("openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

                gl::VertexBufferLayout layout;
                layout << gl::LayoutElement(2) << gl::LayoutElement(2) << gl::LayoutElement(3,GL_UNSIGNED_BYTE,true);

                gl::VertexBuffer buffer(layout, true);
                buffer.push(-255.9f,  255.9f , 0.0f,1.0f, (uchar)255,(uchar)0,(uchar)255);
                buffer.push( 255.9f,  255.9f , 1.0f,1.0f, (uchar)0,(uchar)255,(uchar)255);
                buffer.push(-255.9f, -255.9f , 0.0f,0.0f, (uchar)255,(uchar)255,(uchar)0);
                buffer.push( 255.9f, -255.9f , 1.0f,0.0f, (uchar)255,(uchar)0,(uchar)255);           
                

                gl::VertexBufferLayout layout2;
                layout2 << gl::LayoutElement(2) << gl::LayoutElement(2) << gl::LayoutElement(3,GL_UNSIGNED_BYTE,true) << gl::LayoutElement(1);

                gl::VertexBuffer buffer2(layout2, true);
                buffer2.push(-555.9f,  55.9f , 0.0f,1.0f, (uchar)255,(uchar)0,(uchar)255, 0.1f);
                buffer2.push( 555.9f,  55.9f , 1.0f,1.0f, (uchar)0,(uchar)255,(uchar)255, 0.1f);
                buffer2.push(-555.9f, -55.9f , 0.0f,0.0f, (uchar)255,(uchar)255,(uchar)0, 0.1f);
                buffer2.push( 555.9f, -55.9f , 1.0f,0.0f, (uchar)255,(uchar)0,(uchar)255, 0.1f);  

                buffer.bind();

                gl::Shader shader("res/basicVertex.glsl","res/basicFragment.glsl");

                glm::mat4 mvp = glm::ortho(-400.0f,400.0f,-300.0f,300.0f,-1.0f,1.0f);
                gl::Uniform un(true,mvp);
                shader.pushUniform("MVP",un);

                gl::Texture texture("res/weed.png");

                shader.update();

                while(unsigned int err = glGetError()) {
                    std::cout << err << "\n";
                }
                unsigned int frame = 0;
                bool end = false;
                unsigned int memo;
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

                            case SDL_KEYUP: //recompile
                                if (ev.key.keysym.sym == SDLK_r)
                                    shader.recompile();
                        }
                    }
                    buffer.bind();
                    glClear(GL_COLOR_BUFFER_BIT);
                    unsigned int ibo[] = { 0,1,2,3,1,2 };
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &ibo);

                    buffer2.bind();
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &ibo);
                    if (memo != getMemoryUsage()) {
                        memo = getMemoryUsage();
                        logInfo(memo);
                    }
                    //glDrawArrays(GL_TRIANGLES,0, buffer.getDataCount());
                    SDL_GL_SwapWindow( window );
                    frame++;
                    while (unsigned int err = glGetError())
                        std::cout << err << '\n';
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