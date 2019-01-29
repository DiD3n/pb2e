#include "logger.hpp"


#include <string>
#ifdef WIN32
#include <windows.h>
#endif


void showLogo(void) {
	//why not?
    using namespace std::string_literals;
	_raw(R"(
               88           ad888888b,           
               88          d8"     "88            
               88                  a8P            
   8b,dPPYba,  88,dPPYba,       ,d8P"  ,adPPYba,  
   88P'    "8a 88P'    "8a    a8P"    a8P_____88  
   88       d8 88       d8  a8P'      8PP"""""""  
   88b,   ,a8" 88b,   ,a8" d8"        "8b,   ,aa  
   88`YbbdP"'  8Y"Ybbd8"'  88888888888 `"Ybbd8"'  
   88                                             
## 88 ############%#%##%;;%;"%;.::%;:.:".:'.:' .  '   .
   88                                             
)");
}

std::string getErrorMsg(unsigned int code) {
    switch (code) {
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        case GL_NO_ERROR: default:             return "";
    }
}

void setConsoleColor(unsigned char a) {

#ifdef WIN32  
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, a);
#endif

    //linux?

}