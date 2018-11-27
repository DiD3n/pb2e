#include <iostream>
#include <string>
#include <fstream>

#include "logger.hpp"
#include "include/glew.hpp"

#include "gl/VertexBufferLayout.hpp"
#include "gl/VertexBuffer.hpp"

unsigned int compileShader(int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);//GL_FRAGMENT_SHADER
    std::string shaderSource = source;
    const char * shaderCSource = shaderSource.c_str();
    glShaderSource(shader,1, &shaderCSource,NULL);
 
    glCompileShader(shader);
    
    int compileStatus;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus);
    if (compileStatus != GL_TRUE) {
        int length = 0;
        char message[1024];
        glGetShaderInfoLog(shader,1024,&length,message);
        glDeleteShader(shader);
        logError("compileShader -","[openGL Error]:\n",message,"\n");
        return 0;
    }
    return shader;
}

int main(int argc, char *argv[]) {
    showLogo();

    SDL_Window* window = NULL;
    window = SDL_CreateWindow("openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
                layout << gl::LayoutElement(2) << gl::LayoutElement(3);//,GL_UNSIGNED_BYTE,true);

                gl::VertexBuffer buffer(layout, true);
                buffer.push(-0.9f,  0.9f , 0.9f,0.0f,0.0f);
                buffer.push( 0.9f,  0.9f , 0.0f,0.9f,0.0f);
                buffer.push(-0.9f, -0.9f , 0.0f,0.0f,0.9f);
                buffer.push( 0.9f, -0.9f , 0.9f,0.9f,0.6f);           
                
                buffer.bind();

                unsigned int program = glCreateProgram();

                std::string vertexShaderSource = "";
                {
                    std::ifstream file = std::ifstream ("res/basicVertex.shader",std::ifstream::binary);
                    if (file.good()) {
                        std::string buffer;
                        while (std::getline(file,buffer)) {
                            vertexShaderSource += buffer;
                        }
                    }
                }
                
                std::string fragmentShaderSource = "";
                {
                    std::ifstream file = std::ifstream ("res/basicFragment.shader",std::ifstream::binary);
                     if (file.good()) {
                        std::string buffer;
                        while (std::getline(file,buffer)) {
                            fragmentShaderSource += buffer;
                        }
                    }
                }
                glAttachShader(program,compileShader(GL_VERTEX_SHADER,vertexShaderSource));
                glAttachShader(program,compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource));
                glLinkProgram(program);
                glUseProgram(program);
                
                while(unsigned int err = glGetError()) {
                    std::cout << err << "\n";
                }

                bool end = false;
                while (!end) {

                    SDL_Event ev;
                    while (SDL_PollEvent(&ev)) {
                        switch (ev.type) {
                        case SDL_QUIT:
                            end = true;
                            break;
                        case SDL_WINDOWEVENT:
                            switch (ev.window.event) {
                            case SDL_WINDOWEVENT_SIZE_CHANGED:
                                glViewport(0, 0, ev.window.data1, ev.window.data2);
                                break;
                            }
                            break;
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