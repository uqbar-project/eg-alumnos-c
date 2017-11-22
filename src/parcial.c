#include "parcial.h"
#include <stdlib.h>
#include "commons/constructor.h"

Parcial * Parcial_new(char * materia, int cantidadDePreguntas) {
	NEW(unParcial, Parcial);
	unParcial->materia = materia;
	unParcial->cantidadDePreguntas = cantidadDePreguntas;
	return unParcial;
}
