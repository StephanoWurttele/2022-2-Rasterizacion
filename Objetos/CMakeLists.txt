cmake_minimum_required(VERSION 3.19)
project(Objetos)

set(CMAKE_CXX_STANDARD 20)

add_executable(Objetos basic_lighting_specular.cpp glad.c stb_image.cpp glut_ply.cpp)


target_link_libraries(Objetos -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)