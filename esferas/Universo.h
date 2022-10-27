//
// Created by stephano.wurttele on 20/10/2022.
//

#ifndef LEARNOPENGL_UNIVERSO_H
#define LEARNOPENGL_UNIVERSO_H
#include "Entidad.h"

class Universo {
public:
    int nentidades = 0;
    std::vector<Entidad*> entidades = {};
    glm::vec3 gravity = glm::vec3(0.0f, -0.0005f, 0.0f);

    Universo(){};

    void nuevaEntidad(Objeto *_obj, Shader *_shader, glm::mat4 _modelo = glm::mat4(1.0f));

    void processUniverse();

    void displayUniverse();
};

#endif //LEARNOPENGL_UNIVERSO_H
