cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

#add_executable(LearnOpenGL basic_lighting_specular.cpp glad.c shader_m.h stb_image.h stb_image.cpp)
add_executable(LearnOpenGL geometry_shader_houses.cpp glad.c shader.h stb_image.h stb_image.cpp)
#add_executable(LearnOpenGL model_loading.cpp glad.c shader_m.h stb_image.h stb_image.cpp)

target_link_libraries(LearnOpenGL -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)