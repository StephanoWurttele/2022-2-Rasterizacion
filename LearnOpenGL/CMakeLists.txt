cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearnOpenGL ../piramides/piramides10.cpp glad.c shader_m.h stb_image.h stb_image.cpp)

target_link_libraries(LearnOpenGL -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3dll)