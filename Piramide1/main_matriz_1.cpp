#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shader.h"
#include "mat4.h"

using namespace std;

// v1 v2 v3
// v2 v4 v3
// v1 v2 v4
// v1 v4 v3

float vertices1[] = {
        0, 0, 1,         0.25, -0.5, 1,   0.5, 0.5, 0,
        0.25, -0.5, 1,   0.85, 0, 0,      0.25, -0.5, 0,
        0, 0, 1,         0.25, -0.5, 1,   0.85, 0, 0,
        0, 0, 1,         0.85, 0, 0,      0.5, 0.5, 0,
};

float vertices2[] = {
        0, 0, 0.5,
        0.5, 0, 0.8,
        0.25, 0.25, 0.5,
        0.25, 0.5, 0.7,
};
unsigned int indices2[] = {
        0, 2, 1,
        2, 1, 3,
        0, 2, 3,
        0, 1, 3
};
float tx=0, ty=0;
GLuint p_id;
GLint vertex_id = 0;
GLuint matrix_model_id;

void Redisplay(void) {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glViewport(0, 0, 600, 100);
    glUseProgram(p_id);
    glVertexAttribPointer(vertex_id, 3, GL_FLOAT, GL_FALSE, 0, (const void *)vertices2);
    glEnableVertexAttribArray(vertex_id);

    mat4 matrix_model;
    matrix_model.traslacion(tx, ty, 0);
    GLboolean transpose = GL_TRUE;
    glUniformMatrix4fv(matrix_model_id, 1, transpose, matrix_model.m);

    //glDrawArrays(GL_TRIANGLES, 0, 12);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (const void *) indices2);

    glDisableVertexAttribArray(vertex_id);
    glutSwapBuffers();
}

void setup() {
    CreateShaderProgram("../vertexShader_modelo.vs", "../fragmentShader2.fs", p_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glBindAttribLocation(p_id, vertex_id, "aPos");
    matrix_model_id = glGetUniformLocation(p_id, "matrix_model");
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);
        case 'a': tx -= 0.1; break;
        case 'd': tx += 0.1; break;
        case 'w': ty += 0.1; break;
        case 's': ty -= 0.1; break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(600, 300);

    int nWindow = glutCreateWindow("test");

    glutKeyboardFunc( keyboard );
    glutDisplayFunc( Redisplay );

    //glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutMainLoop();
    return 0;
}
