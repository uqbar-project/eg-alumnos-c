#include "alumno.h"
#include <stdlib.h>
#include "commons/constructor.h"

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

Alumno * Alumno_new(char * nombre,char * direccion,int edad,int legajo,bool (*criterioEstudio)(Parcial *)) {
	//Alumno * unAlumno = malloc(sizeof(Alumno));
	NEW(unAlumno, Alumno);
	unAlumno->nombre=nombre;
	unAlumno->direccion=direccion;
	unAlumno->edad=edad;
	unAlumno->legajo=legajo;
	unAlumno->criterioEstudio = criterioEstudio;
	return unAlumno;
}
