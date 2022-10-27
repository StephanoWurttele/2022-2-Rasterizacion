cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearnOpenGL esferas.cpp Objeto.cpp glad.c Universo.cpp Entidad.cpp )

target_link_libraries(LearnOpenGL -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3dll)