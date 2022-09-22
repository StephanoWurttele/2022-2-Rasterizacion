#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
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
        0, 0, 0,
        0.5, 0, 0,
        0.25, 0.25, 0.5,
        0.25, 0.5, 0,
};
unsigned int indices2[] = {
        0, 2, 1,
        2, 1, 3,
        0, 2, 3,
        0, 1, 3
};
GLuint p_id;
GLint vertex_id = 0;

char* readShader(char *nameFile) {
    FILE* filePointer = fopen(nameFile, "rb");
    char* content = NULL;
    long numVal = 0;
    fseek(filePointer, 0L, SEEK_END);
    numVal = ftell(filePointer);
    fseek(filePointer, 0L, SEEK_SET);
    content = (char*) malloc((numVal+1) * sizeof(char));
    fread(content, 1, numVal, filePointer);
    content[numVal] = '\0';
    fclose(filePointer);
    return content;
}
static void LinkProgram(GLuint id){
    GLint status;
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status) {
        GLint len;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*) malloc(len*sizeof(char));
        glGetProgramInfoLog(id, len, 0, message);
        printf(message);
        free(message);
    }
}
static void CompileShader(GLuint id){
    GLint status;
    glCompileShader(id);
    glGetShaderiv(id, GL_LINK_STATUS, &status);
    if (!status) {
        GLint len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*) malloc(len*sizeof(char));
        glGetShaderInfoLog(id, len, 0, message);
        printf(message);
        free(message);
    }
}
static void CreateShaderProgram (char* vertexShaderFile, char* fragmentShaderFile, GLuint &p_id) {
    char*	vertexShader   = readShader(vertexShaderFile);
    char*	fragmentShader = readShader(fragmentShaderFile);

    /* vertex shader */
    GLuint v_id = glCreateShader(GL_VERTEX_SHADER);
    if (v_id == 0)
        cout << "Could not create vertex shader object";

    glShaderSource(v_id, 1, (const char**) &vertexShader, 0);
    CompileShader(v_id);

    /* fragment shader */
    GLuint f_id = glCreateShader(GL_FRAGMENT_SHADER);
    if (f_id == 0)
        cout << "Could not create fragment shader object";

    glShaderSource(f_id, 1, (const char**) &fragmentShader, 0);
    CompileShader(f_id);

    /* program */
    p_id = glCreateProgram();
    if (p_id == 0)
        cout << "Could not create program object";
    glAttachShader(p_id, v_id);
    glAttachShader(p_id, f_id);
    LinkProgram(p_id);

}

void Redisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(p_id);
    glVertexAttribPointer(vertex_id, 3, GL_FLOAT, GL_FALSE, 0, (const void *)vertices1);
    glEnableVertexAttribArray(vertex_id);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (const void *) indices2);

    glDisableVertexAttribArray(vertex_id);
    glutSwapBuffers();
}

void setup() {
    CreateShaderProgram("../vertexShader.vs", "../fragmentShader.fs", p_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glBindAttribLocation(p_id, vertex_id, "aPos");
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(400, 300);

    int nWindow = glutCreateWindow("test");

    //glutKeyboardFunc( SampleKeyboard );
    glutDisplayFunc( Redisplay );

    //glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutMainLoop();
    return 0;
}
