#ifndef PARCIAL_H_
#define PARCIAL_H_


typedef struct ParcialType {
    char * materia;
    int cantidadDePreguntas;
} Parcial;

Parcial * Parcial_new(char * materia,int cantidadDePreguntas);
void Parcial_free(Parcial *this);

#endif /* PARCIAL_H_ */
