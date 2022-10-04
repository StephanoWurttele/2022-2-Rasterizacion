//
// Created by hgallegos on 4/10/2022.
//

#ifndef PIRAMIDE1_SHADER_H
#define PIRAMIDE1_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

char* readShader(char *nameFile);
void LinkProgram(GLuint id);
void CompileShader(GLuint id);
void CreateShaderProgram (char* vertexShaderFile, char* fragmentShaderFile, GLuint &p_id);

#endif //PIRAMIDE1_SHADER_H
