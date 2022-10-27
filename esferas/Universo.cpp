//
// Created by stephano.wurttele on 20/10/2022.
//

#include "Universo.h"

void Universo::nuevaEntidad(Objeto *_obj, Shader *_shader, glm::mat4 _modelo) {
    entidades.emplace_back(new Entidad(_obj, _modelo, _shader));
    nentidades += 1;
}
void Universo::processUniverse(){
    for(int i = 0; i < nentidades; i++)
        entidades[i]->recalcularPosicion(gravity);
}

void Universo::displayUniverse(){
    for(int i = 0; i < nentidades; i++)
        entidades[i]->display();
}