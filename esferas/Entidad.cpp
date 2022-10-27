//
// Created by stephano.wurttele on 20/10/2022.
//

#include "Entidad.h"
void Entidad::recalcularPosicion(glm::vec3 _aceleracion){
    _velocidad += _aceleracion;
    modelo = glm::translate(modelo, _velocidad);
}

void Entidad::display(){
    obj->display(shader, modelo);
}