cmake_minimum_required(VERSION 3.0.0)
project(pb2e VERSION 0.1.0)

file(GLOB_RECURSE cppf "src/*.cpp")
add_executable(pb2e ${cppf})

#Build counter
file(STRINGS "BuildCounter.txt" BUILD_NUMBER)
math(EXPR BUILD_NUMBER_CALCULATED ${BUILD_NUMBER}+1)
file(WRITE "BuildCounter.txt" ${BUILD_NUMBER_CALCULATED})

add_definitions(-DBuild_Counter=${BUILD_NUMBER_CALCULATED})

target_link_libraries(pb2e -lmingw32)
target_link_libraries(pb2e -lSDL2main)
target_link_libraries(pb2e -lSDL2)
target_link_libraries(pb2e -lSDL2_image)
#target_link_libraries(pb2e -lSDL2_mixer)
target_link_libraries(pb2e -lSDL2_ttf)
target_link_libraries(pb2e -lglew32s -lOpenGL32 -lGLU32)

target_link_libraries(pb2e)