cmake_minimum_required(VERSION 3.0.0)

project(pb2e)

file(GLOB_RECURSE cppf "src/*.cpp")
add_executable(pb2e ${cppf})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Build counter
if(EXISTS "BuildCounter.txt")

    file(STRINGS "BuildCounter.txt" BUILD_NUMBER)
    math(EXPR BUILD_NUMBER_CALCULATED ${BUILD_NUMBER}+1)
    file(WRITE "BuildCounter.txt" ${BUILD_NUMBER_CALCULATED})

endif()


add_definitions(-DBuild_Counter=${BUILD_NUMBER_CALCULATED})


if (${WIN32})

    #MINGW
    target_link_libraries(pb2e -lmingw32 -static-libgcc -static-libstdc++)
    #SDL2
    target_link_libraries(pb2e -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)# -lSDL2_mixer)
    #GL
    target_link_libraries(pb2e -lglew32s -lOpenGL32 -lGLU32)
    #WINDOWS
    target_link_libraries(pb2e -lKernel32 -lPsapi)

    add_definitions(-DCM_WINDOWS)

elseif(${UNIX})

    message("You're using Linux, I don't know if everything works, be careful!")

    #SDL2
    target_link_libraries(pb2e -lSDL2 -lSDL2_image -lSDL2_ttf)# -lSDL2_mixer)
    #GL
    target_link_libraries(pb2e -lGL -lGLEW)

    add_definitions(-DCM_LINUX)

elseif()

    message(FATAL_ERROR "ERROR - Unknown platform!")

endif()

target_link_libraries(pb2e)