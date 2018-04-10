/*
 * tipoAlumno.c
 *
 *  Created on: Apr 9, 2018
 *      Author: juan
 */
#include "tipoAlumno.h"

bool estudioso(Parcial * unParcial) {
	return true;
}

bool hijoDelRigor(Parcial * unParcial) {
	static int cantidadMinimaDePreguntas = 5;
	return hijoDelRigorConMasDe(cantidadMinimaDePreguntas, unParcial);
}

bool hijoDelRigorConMasDe(int cantidadMinimaDePreguntas,
		Parcial* unParcial) {
	return unParcial->cantidadDePreguntas > cantidadMinimaDePreguntas;
}

bool cabulero(Parcial * unParcial) {
	return strlen(unParcial->materia) % 2 == 0;
}
