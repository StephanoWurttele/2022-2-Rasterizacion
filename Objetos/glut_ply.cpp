#include "glut_ply.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

Model_PLY::Model_PLY() {
	/*this->TotalConnectedTriangles = 0;
    this->TotalConnectedPoints = 0;
    this->Faces_Triangles = NULL;
	this->Normals = NULL;
	this->scaleFactor = 1.0;
    this->TotalFaces = 0;
    this->Vertex_Buffer = NULL;
	triangles = new vector<Triangle*>;
	posMin = posMax = Vector3f(0.0f, 0.0f, 0.0f);*/
}

/*
float* Model_PLY::calculateNormal(float *coord1, float *coord2, float *coord3)
{
    // calculate Vector1 and Vector2
    float va[3], vb[3], vr[3], val;
    va[0] = coord1[0] - coord2[0];
    va[1] = coord1[1] - coord2[1];
    va[2] = coord1[2] - coord2[2];

    vb[0] = coord1[0] - coord3[0];
    vb[1] = coord1[1] - coord3[1];
    vb[2] = coord1[2] - coord3[2];

    // cross product
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    // normalization factor
    val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

    float *norm = new float[3];
    norm[0] = -vr[0] / val;
    norm[1] = -vr[1] / val;
    norm[2] = -vr[2] / val;

    return norm;
}*/

int Model_PLY::Load(char* filename) {
//    float sf = 1.0;
//    return this->Load(filename, sf);
//}

//int Model_PLY::Load(char* filename, float sf) {
//    this->TotalConnectedTriangles	= 0;
//    this->TotalConnectedPoints		= 0;

    char* pch = strstr(filename, ".ply");

    if (pch != NULL) {
        FILE* file = fopen(filename, "r");

        /*fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);

        try {
            Vertices = (float*) malloc(ftell(file));
        } catch (char*) {
            return -1;
        }
        if (Vertices == NULL)
            return -1;
        fseek(file, 0, SEEK_SET);*/

        //Faces_Triangles = (float*) malloc(fileSize * sizeof(float));
        //Normales = (float*) malloc(fileSize * sizeof(float));
        //Indices  = (float*) malloc(fileSize * sizeof(float));

        if (file) {
            int		i = 0;
            //int		temp = 0;
            //int		quads_index = 0;
            //int		triangle_index = 0;
            int		normal_index = 0;
            char	buffer[1000];

            fgets(buffer, 1000, file);			// ply

            // READ HEADER
            // -----------------
            // Find number of vertexes
            while (strncmp("element vertex", buffer, strlen("element vertex")) != 0) {
                fgets(buffer, 300, file);			// format
            }
            strcpy(buffer, buffer + strlen("element vertex"));
            sscanf(buffer, "%i", &this->cantVertices);
            //Vertices = (float*) malloc(cantVertices * 3 * sizeof(float));
            //Normales = (float*) malloc(cantVertices * 3 * sizeof(float));
            Vertices = (float*) malloc(cantVertices * 6 * sizeof(float));

            // Find number of faces
            fseek(file, 0, SEEK_SET);
            while (strncmp("element face", buffer, strlen("element face")) != 0) {
                fgets(buffer, 300, file);			// format
            }
            strcpy(buffer, buffer + strlen("element face"));
            sscanf(buffer, "%i", &this->cantIndices);
            Indices = (unsigned int*) malloc(cantIndices * 3 * sizeof(unsigned int));

            // go to end_header
            while (strncmp("end_header", buffer, strlen("end_header")) != 0) {
                fgets(buffer, 300, file);			// format
            }

            //----------------------
            // read verteces
            i = 0;
            int iterator;
            for (iterator = 0; iterator < this->cantVertices; iterator++) {
                fgets(buffer, 300, file);

                /*sscanf(buffer, "%f %f %f %f %f %f",
                       &Vertices[i], &Vertices[i + 1], &Vertices[i + 2],
                       &Normales[i], &Normales[i + 1], &Normales[i + 2]);*/
                sscanf(buffer, "%f %f %f %f %f %f",
                       &Vertices[i], &Vertices[i + 1], &Vertices[i + 2],
                       &Vertices[i+3], &Vertices[i + 4], &Vertices[i + 5]);
                //std::cout << Vertices[i] << "\t" << Vertices[i+1] << "\t" << Vertices[i+2] << std::endl;

				//Vertices[i]	 *= sf;
                //Vertices[i + 1] *= sf;
                //Vertices[i + 2] *= sf;
                i += 6;
            }

            // read faces
            i = 0;
            for (iterator = 0; iterator < this->cantIndices; iterator++) {
                fgets(buffer, 300, file);

                if (buffer[0] == '3') {
                    int idx1 = 0, idx2 = 0, idx3 = 0;
                    //sscanf(buffer,"%i%i%i\n", vertex1,vertex2,vertex3 );
                    buffer[0] = ' ';
                    sscanf(buffer, "%i %i %i", &Indices[i], &Indices[i+1], &Indices[i+2]);
                    //std::cout << Indices[i] << "\t" << Indices[i+1] << "\t" << Indices[i+2] << std::endl;


                }

                i += 3;
            }
            fclose(file);
            printf("Finish!!\n");
        } else {
            printf("File can't be opened\n");
        }
    } else {
        printf("File does not have a .PLY extension. ");
    }
    return 0;
}

void Model_PLY::imprimir() {
    std::cout << "\nVertices:\n";
    for (int i = 0; i < cantVertices*6; i+=6) {
        std::cout << Vertices[i] << " " << Vertices[i+1]
                << " " << Vertices[i+2] << " " << Vertices[i+3]
                << " " << Vertices[i+4] << " " << Vertices[i+5] << std::endl;
    }
    std::cout << "\nIndices: \n";
    for (int i=0; i < cantIndices*3; i+=3) {
        std::cout << Indices[i] << " " << Indices[i+1]
                << " " << Indices[i+2] << std::endl;
    }
}

int Model_PLY::enviar_GPU() {
    glGenVertexArrays(1, &vao);
    GLuint vbos[2];
    glGenBuffers(2, vbos);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, cantVertices*6*sizeof(float), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(POSITION_ATTRIBUTE,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(POSITION_ATTRIBUTE);

    glVertexAttribPointer(NORMAL_ATTRIBUTE,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(NORMAL_ATTRIBUTE);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbos[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, cantIndices * 3 * sizeof(GLuint), Indices, GL_STATIC_DRAW );
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    return vao;
}

void Model_PLY::display(Shader &sh) {
    mat4 model = mat4(1.0);
    model = scale(model, vec3(0.5));
    //model = translate(model, centro);
    sh.setMat4("model", model);
    if (true) {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, cantIndices*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}