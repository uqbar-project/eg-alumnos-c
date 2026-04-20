#include "criterio.h"

bool estudioso(Parcial * unParcial) {
	return true;
}

bool hijoDelRigor(Parcial * unParcial) {
	const int cantidadMinimaDePreguntas = 5;
	return hijoDelRigorConMasDe(cantidadMinimaDePreguntas, unParcial);
}

bool hijoDelRigorConMasDe(int cantidadMinimaDePreguntas,
		Parcial* unParcial) {
	return unParcial->cantidadDePreguntas > cantidadMinimaDePreguntas;
}

bool cabulero(Parcial * unParcial) {
	return strlen(unParcial->materia) % 2 != 0;
}
