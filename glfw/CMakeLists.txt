cmake_minimum_required(VERSION 3.19)
project(glfw)

set(CMAKE_CXX_STANDARD 20)

add_executable(glfw glad.c piramide_1.cpp mat4.h)

target_link_libraries(glfw -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)