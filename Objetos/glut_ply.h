#ifndef GLUT_PLY_H
#define GLUT_PLY_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader_m.h"
using namespace std;
using namespace glm;

class Model_PLY {
public:
	Model_PLY();

    int		Load(char *filename);
//    int		Load(char *filename, float scaleFactor);
//    void	Draw();
//    float*	calculateNormal(float *coord1, float *coord2, float *coord3);
//    void	transform(Matrix4f transformation);

//    float	*Faces_Triangles;
    float	*Vertices;
    float	*Normales;
    unsigned int     *Indices;

    int     cantVertices;
    int     cantIndices;
    GLuint vao;
    GLint POSITION_ATTRIBUTE=0, NORMAL_ATTRIBUTE=1;
    void imprimir();
    int enviar_GPU();
    void display(Shader &sh);

	// Position min and max for AABB
//	Vector3f posMin, posMax;
};

#endif
