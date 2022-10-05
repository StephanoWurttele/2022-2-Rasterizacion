cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearnOpenGL basic_lighting_diffuse.cpp glad.c shader_m.h stb_image.h stb_image.cpp ../Objetos/Objeto.cpp ../Objetos/Objeto.h)

target_link_libraries(LearnOpenGL -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)