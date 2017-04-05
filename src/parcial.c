#include "parcial.h"
#include <stdlib.h>

Parcial * Parcial_new(char * materia, int cantidadDePreguntas) {
	Parcial * unParcial = malloc(sizeof(Parcial));
	unParcial->materia = materia;
	unParcial->cantidadDePreguntas = cantidadDePreguntas;
	return unParcial;
}
void Parcial_free(Parcial *this) {
	free(this);
}
