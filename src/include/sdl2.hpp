#pragma once

/* 
SDL 2.0 and newer are available under the zlib license :

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mix.h>


inline const char* initSDL() //returns "" when success
{
    /*   SDL2  */

    if ( SDL_Init(SDL_INIT_EVENTS) != 0 ) 
    {
        return SDL_GetError();
    }

    /*   IMG   */

    int img_flags = IMG_INIT_WEBP| IMG_INIT_JPG | IMG_INIT_PNG;
    if ( !( IMG_Init( img_flags ) & img_flags ) ) 
    {
        return SDL_GetError();
    }

    /*   TTF   */

    if( TTF_Init() != 0 ) 
    {
        return SDL_GetError();
    }

    /*   MIX   

    int mix_flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if( !( MIX_Init( mix_flags ) & mix_flags ) ) 
    {
        return SDL_GetError();
    }

    */

    return "";

}

inline void quitSDL() 
{

    SDL_Quit();

    IMG_Quit();

    TTF_Quit();

    //Mix_Quit();

}
