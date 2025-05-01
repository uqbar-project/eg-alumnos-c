#ifndef PARCIAL_H_
#define PARCIAL_H_

#include "commons/string.h"

typedef struct ParcialType {
    string materia;
    int cantidadDePreguntas;
} Parcial;

Parcial * Parcial_new(string materia,int cantidadDePreguntas);

#endif /* PARCIAL_H_ */
