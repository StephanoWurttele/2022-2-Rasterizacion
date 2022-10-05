cmake_minimum_required(VERSION 3.19)
project(2022_2_Rasterizacion)

set(CMAKE_CXX_STANDARD 20)

#add_executable(2022_2_Rasterizacion glmatrix.c glmatrix.h shapes.c)
add_executable(2022_2_Rasterizacion main.cpp)

target_link_libraries(2022_2_Rasterizacion -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)