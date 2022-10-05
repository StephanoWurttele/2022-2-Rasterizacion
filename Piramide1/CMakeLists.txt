cmake_minimum_required(VERSION 3.19)
project(Piramide1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Piramide1 shader.cpp shader.h main_matriz_1.cpp mat4.h)

target_link_libraries(Piramide1 -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3  -lglew32)