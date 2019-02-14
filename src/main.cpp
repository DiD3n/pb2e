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

#include "gui/object.hpp"

#include "system/memory.hpp"

typedef unsigned char uchar;

int main(int argc, char *argv[])
{
    showLogo(); //the most important thing

    /*  SDL2 INIT */
    int exitCode = EXIT_SUCCESS;
    {
        const char* err = initSDL();
        if (err != "") 
        {
            logError(err);
            exitCode = EXIT_FAILURE;
        }
    }
        

    /*    WINDOW    */

    SDL_Window* window = NULL;
    SDL_GLContext context = nullptr;
    window = SDL_CreateWindow("pb2e - openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) 
    {
        logError("SDL_CreateWindow");
        exitCode = EXIT_FAILURE;
    }

    context = SDL_GL_CreateContext(window);

    if (!context) 
    {
       logError("SDL_GL_CreateContext");
       exitCode = EXIT_FAILURE;
    }

    /*   GLEW INIT  */
    {
        unsigned int initErr = glewInit();
        if (initErr != GLEW_OK) 
        {
            logError("glewInit");
            exitCode = EXIT_FAILURE;
        }

    }

    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
		logError("Vsync problem!");
	}
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    logInfo("SDL2 & openGL Init - done!");

    {
           
        gl::Renderer renderer;
        gl::Texture texture("res/weed.png", gl::nearest);
        gl::Shader shader("res/basicVertex.glsl","res/basicFragment.glsl");
        gl::Shader shader2("res/basicUIVert.glsl","res/basicUIFrag.glsl");
        gl::FrameBuffer frameBuffer({800,600});

        glm::mat4 mvp = glm::ortho(-400.0f,400.0f,-300.0f,300.0f,-1.0f,1.0f);
                
        //default style
        const std::shared_ptr<gui::Style> style(new gui::Style());
        gui::Object object(std::string("test"),style);

        {

            shader.pushUniform("MVP",{true,mvp});
            shader2.pushUniform("MVP",{true,mvp});
            style->shader.pushUniform("MVP",{true,mvp});

            gl::VertexBufferLayout layout;
            layout.push(2).push(2).push(3,GL_UNSIGNED_BYTE,true);
            renderer.pushCustomBuffer(layout,frameBuffer.getAsTexture(),shader);
            renderer.pushCustomBuffer(layout,texture,shader);
                    
            gl::VertexBufferLayout colorLayout;
            colorLayout.genFromShaderAttrib(shader2);

            renderer.pushCustomBuffer(colorLayout,shader2);
            renderer.pushCustomBuffer(colorLayout,style->shader);

        }
                   
        gl::Rectf weedSize(-400.f,-300.f,800.f,600.f);      
        gl::Rectf rectt(-50.f,-50.f,300.f,300.f);
        gl::Rectf screenRect(0,0,800,600);
 
        unsigned int frame = 0;
        bool end = false;
        while (!end) {
                    
            SDL_Event ev;
            while (SDL_PollEvent(&ev)) 
            {
                switch (ev.type) 
                {
                case SDL_QUIT: //exit
                        end = true;
                    break;

                case SDL_WINDOWEVENT: //resize
                        if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) 
                        {
                            int w = ev.window.data1, h = ev.window.data2;
                            glViewport(0, 0, w, h);
                            mvp = glm::ortho(-(float)w/2,(float)w/2,-(float)h/2,(float)h/2,-1.0f,1.0f);

                            //update shaders
                            shader.update("MVP");
                            shader2.update("MVP");

                            //update framebuffer & rect
                            frameBuffer.setSize({(unsigned int)w,(unsigned int)h});
                            screenRect.w = w;
                            screenRect.h = h;
                            break;
                        }
                    break;

                case SDL_MOUSEWHEEL:
                    float c;

                    if(ev.wheel.y > 0)
                        c = weedSize.h* 1.1f - weedSize.h;
                    else if(ev.wheel.y < 0)
                        c = weedSize.h* 0.9f - weedSize.h;

                    weedSize.w += c;
                    weedSize.h += c;
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
            //frameBuffer.clear();
            {   //render to frameBuffer

                renderer.draw<gl::rectangle>(shader,texture,weedSize,(uchar)32,(uchar)255,(uchar)255);
                renderer.draw<gl::rectangle>(shader,texture,rectt,(uchar)255,(uchar)255,(uchar)0);

                std::array<gl::Vector2f,3> arr = {gl::Vector2f(-500,500),gl::Vector2f(-500,-500),gl::Vector2f(500,-500)};
                renderer.draw<3>(shader,texture,arr,1.f,1.f);

            }
            renderer.finalRender();
            //frameBuffer.use(false);
            renderer.clear();
            {   //render to screen

                gl::Color color(1.f,0.25f,1.f,0.5f);
                object.draw(renderer);

            }
            renderer.finalRender();

            SDL_GL_SwapWindow( window );
            frame++;
            while (unsigned int err = glGetError())
                logError(err);
        }
    }


    main_exit:

    /* some cleanup  */

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();

    if (exitCode)
        std::cin.get();

    return exitCode;
}