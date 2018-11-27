#include "logger.hpp"

#include <string>

void showLogo(void) {
	//why not?
    using namespace std::string_literals;
	log(R"(
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
