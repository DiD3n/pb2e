#include <iostream>
#include <string>
#include <fstream>

#define _DEBUG

#include "logger.hpp"
#include "include/glew.hpp"

#include "gl/VertexBufferLayout.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/Shader.hpp"
#include "gl/Texture.hpp"


int main(int argc, char *argv[]) {
    showLogo();

    SDL_Window* window = NULL;
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
                layout << gl::LayoutElement(2) << gl::LayoutElement(2);

                gl::VertexBuffer buffer(layout, true);
                buffer.push(-0.9f,  0.9f , 0.0f,1.0f);
                buffer.push( 0.9f,  0.9f , 1.0f,1.0f);
                buffer.push(-0.9f, -0.9f , 0.0f,0.0f);
                buffer.push( 0.9f, -0.9f , 1.0f,0.0f);           
                
                buffer.bind();

                gl::Shader shader("res/basicVertex.glsl","res/basicFragment.glsl");

                gl::Texture texture("res/weed.png");

                while(unsigned int err = glGetError()) {
                    std::cout << err << "\n";
                }

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
                                    glViewport(0, 0, ev.window.data1, ev.window.data2);
                                    break;
                                }
                            break;

                            case SDL_KEYUP: //recompile
                                if (ev.key.keysym.sym == SDLK_r)
                                    shader.recompile();
                        }
                    }
                    glClear(GL_COLOR_BUFFER_BIT);
                    
                    unsigned int ibo[] = { 0,1,2,3,1,2 };
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &ibo);
                    
                    //glDrawArrays(GL_TRIANGLES,0, buffer.getDataCount());
                    SDL_GL_SwapWindow( window );

                    while (unsigned int err = glGetError())
                        std::cout << err << '\n';
                }
            }
        }
        SDL_GL_DeleteContext(context);
    }
    SDL_DestroyWindow(window);
    return EXIT_SUCCESS;
}