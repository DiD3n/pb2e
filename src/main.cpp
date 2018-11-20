#include <iostream>
#include <string>
#include <fstream>

#include "logger.hpp"
#include "include/glew.hpp"

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
    
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
					logError("Vsync problem");
				}
                float vertexData[] = {
                    -0.5f,  0.7f, 
                     0.0f, -0.9f, 
                     0.1f, -0.7f,

                     0.9f, -0.8f,
                    -0.5f,  0.7f, 
                     0.0f, -0.1f, 

                     0.4f, -0.7f,
                     0.9f, -0.8f, 
                     0.8f,  0.9f, 
                     
                    -0.8f,  0.2f,
                     0.8f,  0.9f, 
                    -0.8f,  0.2f,

                     0.1f, -0.7f,
                     0.9f, -0.8f,
                    -0.5f,  0.7f
                };

                unsigned int VBO;
                glGenBuffers(1,&VBO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO );
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
                log(sizeof(vertexData));
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,/*2*sizeof(float)*/0,0);
                glEnableVertexAttribArray(0);

                //////////
                //shader

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
                
                {
                    unsigned int err = glGetError();
                    if (err)
                        std::cout << err;
                }

                while(unsigned int err = glGetError()) {
                    std::cout << err << " Shader" << "\n";
                }
                    
                bool end = false;
                std::cout << "Start While";
                while (!end) {
                    SDL_Event ev;
                    while (SDL_PollEvent(&ev)) {
                        switch (ev.type) {
                            case SDL_QUIT:
                            end = true;
                            break;
                        }
                    }
                    int windowWidth,windowHeight;
                    SDL_GetWindowSize(window,&windowWidth,&windowHeight);
                    glViewport(0,0,windowWidth,windowHeight);
                    {
                        unsigned int err = glGetError();
                        if (err)
                            std::cout << err;
                    }
                    glClear(GL_COLOR_BUFFER_BIT);

                    unsigned int ibo[] = {
                        1,2,3, 4,5,6, 7,8,9, 10,11,12, 13,14,15
                    };
                    glDrawElements( GL_TRIANGLES, 16,GL_UNSIGNED_INT,&ibo);
                    //glDrawArrays(GL_LINE_STRIP_ADJACENCY,0,12);
                    SDL_GL_SwapWindow( window );
                }
            }
            SDL_GL_DeleteContext(context);
        }
        SDL_DestroyWindow(window);
    }
    std::cin.get();
    return EXIT_SUCCESS;
}