//
// Created by stephano.wurttele on 20/10/2022.
//

#ifndef LEARNOPENGL_ENTIDAD_H
#define LEARNOPENGL_ENTIDAD_H

#include "Objeto.h"
class Entidad {
public:
    glm::mat4 modelo;
    Objeto *obj;
    Shader *shader;
    Entidad(Objeto *_obj, glm::mat4 _modelo, Shader *sh){
        obj = _obj;
        modelo = _modelo;
        shader = sh;
    };
    glm::vec3 _velocidad = glm::vec3(0.06f, 0.08f, 0.0f);
    void recalcularPosicion(glm::vec3 _aceleracion);
    void display();
};


#endif //LEARNOPENGL_ENTIDAD_H
